#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include<stdlib.h>
#include <iostream>
#define FCBNAMELEN 16
typedef int ID, TYPE, SIZE;
using namespace std;
enum { EMPTY, ROUTINE, FOLDER };

const char* myfilepath = "./myfile";/*常量设置*/
const int BLOCKSIZE = 256;       //盘块大小
const int MAXOPEN = 5;          //能打开最多的文件数
const int BLOCKNUM = 64;   //盘块数
const int DISKSIZE = BLOCKSIZE * BLOCKNUM;    //磁盘大小

typedef struct FCB {
	char fcb_name[FCBNAMELEN];
	SIZE size;
	TYPE type;
	ID father_block_id;//父块块号
	ID block_id;//当前块号
	void fcb_init()
	{
		strcpy(fcb_name, "\0");
		size = 0;
		type = EMPTY;
		father_block_id = 0;
		block_id = 0;
	}
}FCB;

int now_openfile_num = 0;
const SIZE MAXFCBNUM = BLOCKSIZE / sizeof(FCB);

typedef struct NOWOPENLIST {
	FCB fcb[MAXOPEN];
	SIZE open_num;
	NOWOPENLIST()
	{
		open_num = 0;
		for (int i = 0; i < MAXOPEN; ++i)
		{
			fcb[i].father_block_id = -1;
			fcb[i].type = ROUTINE;
		}
	}
}NOWOPENLIST;

typedef struct dirFile {
	FCB fcb[MAXFCBNUM];
	void dirFile_init(ID father_black_id, ID block_id,const char* name)
	{
		for (int i = 0; i < MAXFCBNUM; ++i)
		{
			if (!i)
			{
				fcb[i].father_block_id = father_black_id;
				fcb[i].block_id = block_id;
				fcb[i].type = FOLDER;
				strcpy(fcb[i].fcb_name, name);
			}//第一块为目录块
			else
			{
				fcb[i].type = EMPTY;
				fcb[i].father_block_id = block_id;
			}
		}
	}
}dirFile;

typedef struct DISK {
	int FAT1[BLOCKNUM];
	int FAT2[BLOCKNUM];
	dirFile root;//根目录
	char data[BLOCKNUM - 3][BLOCKSIZE];
	void Format()
	{
		memset(FAT1, 0, BLOCKNUM);
		memset(FAT2, 0, BLOCKNUM);
		FAT1[0] = FAT1[1] = FAT1[2] = -2;
		FAT2[0] = FAT2[1] = FAT2[2] = -2;
		root.dirFile_init(2, 2,"./");
		memset(data, 0, sizeof(data));
	}
}DISK;

FILE* fp;
char* BaseAddress;//该虚拟空间的基地址
string currentPath = "./";
//char* input_file_name;
ID now_block_id = 2;
DISK* osPointer;
char command[16];
string cmd;
NOWOPENLIST* openlist;

void  Format()
{
	now_block_id = 2;
	currentPath = "./";
	osPointer->Format();
	delete openlist;
	openlist = new NOWOPENLIST;
	fp = fopen(myfilepath, "w+");
	fwrite(BaseAddress, sizeof(char), DISKSIZE, fp);
	fclose(fp);
	cout << "格式化成功" << endl;
	return;
}
bool write_file(char* name)
{
	char* begin_pos;
	char* end_pos;
	int pos;
	for (pos = 0; pos < MAXOPEN; ++pos)
	{
		if (strcmp(openlist->fcb[pos].fcb_name, name) == 0)
		{
			if (openlist->fcb[pos].father_block_id == now_block_id) break;
			else
			{
				cout << "该文件处于打开列表中，本系统只能改写当前目录下的文件" << endl;
				return false;
			}
		}
	}
	if (pos == MAXOPEN)
	{
		cout << "该文件尚未打开，请先打开再写入文件" << endl;
		return false;
	}
	int now_pos = pos;
	ID file_start_id = openlist->fcb[now_pos].block_id - 3;
	begin_pos = osPointer->data[file_start_id];
	end_pos = osPointer->data[file_start_id + 1];
	cout << "请输入文本以Ctrl+D结束" << endl;
	//memset(begin_pos, 4, sizeof(char) * BLOCKSIZE);//尤为关键，重置之前字符数组，防止修改失效
	char input;
	while (((input = getchar()) != 4)) {
		if (begin_pos < end_pos - 1) {
			*begin_pos++ = input;
		}
		else {
			cout << "达到单体文件最大容量！";
			*begin_pos++ = 4;
			break;
		}
	}
	return true;
}
bool read_file(char* name)
{
	int pos;
	for (pos = 0; pos < MAXOPEN; ++pos)
	{
		if (strcmp(openlist->fcb[pos].fcb_name, name) == 0)
		{
			if (openlist->fcb[pos].father_block_id == now_block_id) break;
			else {
				cout << "本系统只能读取当前目录下文件" << endl;
				return false;
			}
		}
	}
	if (pos == MAXOPEN)
	{
		cout << "该文件尚未打开，请打开后再读取信息" << endl;
		return false;
	}

	int now_pos = pos;
	ID  file_start_id = openlist->fcb[now_pos].block_id - 3;
	char* begin_pos = osPointer->data[file_start_id];
	char* end_pos = osPointer->data[file_start_id + 1];
	cout << "文件内容为:" << endl;
	while ((*begin_pos) != 4 && (begin_pos < end_pos))
	{
		//输出read
		putchar(*begin_pos++);
	}
	cout << endl;
	return true;
}
bool open_file(char* name)
{
	for (int i = 0; i < MAXOPEN; ++i)
	{
		if (openlist->fcb[i].type == ROUTINE && strcmp(openlist->fcb[i].fcb_name, name) == 0 && openlist->fcb[i].father_block_id == now_block_id)
		{
			cout << "该文件已被打开" << endl;
			return false;
		}
	}
	if (openlist->open_num == MAXOPEN)
	{
		cout << "打开文件数目达到上限" << endl;
		return false;
	}

	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);

	int pos;
	int fcb_pos;
	for (pos = 1; pos < MAXFCBNUM; ++pos)
	{
		if (nowdir->fcb[pos].type == ROUTINE && strcmp(nowdir->fcb[pos].fcb_name, name) == 0)
		{
			fcb_pos = pos;
			break;
		}
	}
	if (pos == MAXFCBNUM)
	{
		cout << "当前目录下不存在该文件" << endl;
		return false;
	}
	openlist->fcb[now_openfile_num] = nowdir->fcb[fcb_pos];
	openlist->open_num++;
	now_openfile_num++;
	cout << "文件打开成功" << endl;
	return true;
}
bool close_file(char* name)
{
	int pos;
	for (pos = 0; pos < MAXOPEN; ++pos)
	{
		if (openlist->fcb[pos].type == ROUTINE && strcmp(openlist->fcb[pos].fcb_name, name) == 0)
		{
			if (openlist->fcb[pos].father_block_id == now_block_id) break;
			else {
				cout << "该文件已打开，但不在当前目录下，无法关闭" << endl;
				return false;
			}
		}
	}
	if (pos == MAXOPEN)
	{
		cout << "该文件不在打开列表,不需要关闭" << endl;
		return false;
	}
	openlist->open_num--;
	openlist->fcb[pos].fcb_init();
	now_openfile_num--;
	cout << "该文件已关闭" << endl;
	return true;
}
void  mkdir(char* name)
{
	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);
	for (int i = 1; i < MAXFCBNUM; ++i)//检查同一目录是否存在同名文件夹
	{
		if (nowdir->fcb[i].type == FOLDER && strcmp(nowdir->fcb[i].fcb_name, name) == 0)
		{
			cout << "该文件夹下存在同名文件夹" << endl;
			return;
		}
	}
	int pos;
	for (pos = 1; pos < MAXFCBNUM; ++pos)//查找是否存在空白fcb
	{
		if (nowdir->fcb[pos].type == EMPTY) break;
	}
	if (pos == MAXFCBNUM)
	{
		cout << "该目录已满！请选择新的目录下创建" << endl;
		return;
	}
	ID now_fcb_pos = pos;
	int j;
	for (j = 3; j < BLOCKNUM; ++j)//查找是否存在空的硬盘块
	{
		if (osPointer->FAT1[j] == 0) break;
	}
	if (j == BLOCKNUM)
	{
		cout << "硬盘已满" << endl;
		return;
	}
	ID now_FAT_pos = j;
	osPointer->FAT1[now_FAT_pos] = osPointer->FAT2[now_FAT_pos] = 2;
	strcpy(nowdir->fcb[now_fcb_pos].fcb_name, name);
	nowdir->fcb[now_fcb_pos].type = FOLDER;
	nowdir->fcb[now_fcb_pos].father_block_id = now_block_id;
	nowdir->fcb[now_fcb_pos].block_id = now_FAT_pos;

	nowdir = (dirFile*)(osPointer->data[now_FAT_pos - 3]);
	nowdir->dirFile_init(now_block_id, now_FAT_pos, name);
	cout << "创建子目录成功" << endl;
	return;
}
void rmdir(char* name)
{
	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);

	int pos;
	for (pos = 1; pos < MAXFCBNUM; ++pos)//检查同一目录是否存在同名文件
	{
		if (nowdir->fcb[pos].type == FOLDER && strcmp(nowdir->fcb[pos].fcb_name, name) == 0)
			break;
	}
	ID find_fcb_pos = pos;
	if (find_fcb_pos == MAXFCBNUM)
	{
		cout << "当前目录下不存在该子目录" << endl;
		return;
	}
	ID id = nowdir->fcb[find_fcb_pos].block_id;
	dirFile* sonDir;
	sonDir = (dirFile*)(osPointer->data[id - 3]);
	for (int i = 1; i < MAXFCBNUM; ++i)
	{
		if (sonDir->fcb[i].type != EMPTY)
		{
			cout << "该文件夹非空，请先删除文件夹中内容操作" << endl;
			return;
		}
	}
	osPointer->FAT1[id] = osPointer->FAT2[id] = 0;//FAT清空
	char* x = osPointer->data[id - 3];
	memset(x, 0, BLOCKSIZE);
	nowdir->fcb[find_fcb_pos].fcb_init();
	cout << "删除当前目录下的文件夹成功" << endl;
	return;
}
void mkfile(char* name)
{
	dirFile* nowdir;
	int empty_num = 0;
	bool found = false;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);

	for (int i = 1; i < MAXFCBNUM; ++i)
	{
		if (nowdir->fcb[i].type == EMPTY && !found)
		{
			empty_num = i;
			found = true;
		}
		else if (nowdir->fcb[i].type == ROUTINE && strcmp(nowdir->fcb[i].fcb_name, name) == 0)
		{
			cout << "无法在同一目录下创建同名文件" << endl;
			return;
		}
	}
	if (!empty_num)
	{
		cout << "已经达到目录项容纳上限，无法创建新目录" << endl;
		return;
	}

	int pos;
	for (pos = 3; pos < BLOCKNUM; ++pos)//查找FAT寻找空白区，用于分配磁盘块号
	{
		if (osPointer->FAT1[pos] == 0) break;
	}
	if (pos == BLOCKNUM)
	{
		cout << "磁盘已满" << endl;
		return;
	}

	int now_FAT_pos = pos;
	osPointer->FAT1[now_FAT_pos] = osPointer->FAT2[now_FAT_pos] = 1;
	strcpy(nowdir->fcb[empty_num].fcb_name, name);
	nowdir->fcb[empty_num].type = ROUTINE;
	nowdir->fcb[empty_num].father_block_id = now_block_id;
	nowdir->fcb[empty_num].block_id = now_FAT_pos;
	nowdir->fcb[empty_num].size = 0;

	char* x = osPointer->data[now_FAT_pos - 3];
	memset(x, 4, BLOCKSIZE);
	cout << "在当前目录下创建文本文件成功" << endl;
	return;
}
void delete_file(char* name)
{
	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);
	int i;
	for (i = 1; i < BLOCKNUM; ++i)//找文件
	{
		if (nowdir->fcb[i].type == ROUTINE && strcmp(nowdir->fcb[i].fcb_name, name) == 0)
			break;
	}
	if (i == BLOCKNUM)
	{
		cout << "当前目录下不存在该文件" << endl;
		return;
	}

	int j;
	for (j = 0; j < MAXOPEN; ++j)//找当前打开的文件
	{
		if (openlist->fcb[j].type == ROUTINE && strcmp(openlist->fcb[j].fcb_name, name) == 0)
		{
			if (openlist->fcb[j].father_block_id == now_block_id) break;
			else
			{
				cout << "该文件未在当前目录下" << endl;
				return;
			}
		}
	}
	if (j != MAXOPEN) close_file(name);//删完关闭文件

	int now_fcb_pos = i;
	int id = nowdir->fcb[now_fcb_pos].block_id;
	osPointer->FAT1[id] = osPointer->FAT2[id] = 0;
	char* x = osPointer->data[id - 3];
	memset(x, 0, BLOCKSIZE);
	nowdir->fcb[now_fcb_pos].fcb_init();
	cout << "删除成功" << endl;
	return;
}
void dir()
{
	int folder_count = 0;
	int file_count = 0;
	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);
	for (int i = 1; i < MAXFCBNUM; ++i)
	{
		if (nowdir->fcb[i].type == ROUTINE)
		{
			file_count++;
			cout << nowdir->fcb[i].fcb_name << "\t文本文件" << endl;
		}
		if (nowdir->fcb[i].type == FOLDER)
		{
			folder_count++;
			cout << nowdir->fcb[i].fcb_name << "\t文件夹" << endl;
		}
	}
	cout << "\n该目录下共有" << file_count << "个文本文件," << folder_count << "个文件夹" << endl;
	return;
}
bool changePath(char* name)
{
	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);
	if (strcmp(name, "..") == 0)
	{
		if (now_block_id == 2)
		{
			cout << "当前目录即为根目录" << endl;
			return false;
		}
		now_block_id = nowdir->fcb[0].father_block_id;
		currentPath = currentPath.substr(0, currentPath.size() - strlen(nowdir->fcb[0].fcb_name) - 1);
		return true;
	}
	int pos;
	for (pos = 1; pos < MAXFCBNUM; ++pos)
	{
		if (nowdir->fcb[pos].type == FOLDER && strcmp(nowdir->fcb[pos].fcb_name, name) == 0)
		{
			break;
		}
	}
	if (pos == MAXFCBNUM)
	{
		cout << "不存在该目录" << endl;
		return false;
	}
	now_block_id = nowdir->fcb[pos].block_id;
	currentPath = currentPath + nowdir->fcb[pos].fcb_name + "\\";
	cout << "进入当前目录下的子目录成功" << endl;
	return true;
}
void save() {
	fp = fopen(myfilepath, "w+");
	fwrite(BaseAddress, sizeof(char), DISKSIZE, fp);
	fclose(fp);
	//释放内存上的虚拟磁盘
	free(osPointer);
	//释放用户打开文件表
	delete openlist;
	cout<<"退出文件系统成功！\n\n";
	return;
}


int main()
{
	printf("/**************   以下是使用介绍：   *************\\\n");
	printf("/**************   mkfile: 创建文件   *************\\\n");
	printf("/**************   mkdir:创建文件夹   *************\\\n");
	printf("/**************   rmfile: 删除文件   *************\\\n");
	printf("/**************   rmdir:删除文件夹   *************\\\n");
	printf("/**************   cd  :   更改路径   *************\\\n");
	printf("/**************   dir:显示当前路径内容   *********\\\n");
	printf("/**************   open:   打开文件   *************\\\n");
	printf("/**************   close:  关闭文件   *************\\\n");
	printf("/**************   read:     读文件   *************\\\n");
	printf("/**************   write:    写文件   *************\\\n");
	printf("/**************   format:   格式化   *************\\\n");
	printf("/**************   exit:       退出   *************\\\n");
	openlist = new NOWOPENLIST;//创建用户文件打开表
	BaseAddress = (char*)malloc(DISKSIZE);//申请虚拟空间并且初始化
	osPointer = (DISK*)(BaseAddress);//虚拟磁盘初始化	
	if ((fp = fopen(myfilepath, "r")) != NULL) {//加载磁盘文件
		fread(BaseAddress, sizeof(char), DISKSIZE, fp);
		printf("加载磁盘文件( %s )成功,现在可以进行操作了!\n\n", myfilepath);
	}
	else {
		printf("这是你第一次使用该文件管理系统!\t正在初始化...\n");
		Format();
		printf("初始化已经完成,现在可以进行操作了!\n\n");
	}
	while (1) {
		cout << currentPath;
		cin >> cmd;
		if (cmd == "format") {
			Format();
		}
		else if (cmd == "mkdir") {
			cin >> command;
			mkdir(command);
		}
		else if (cmd == "rmdir") {
			cin >> command;
			rmdir(command);
		}
		else if (cmd == "dir") {
			dir();
		}
		else if (cmd == "cd") {
			cin >> command;
			changePath(command);
		}
		else if (cmd == "mkfile") {
			cin >> command;
			mkfile(command);
		}

		else if (cmd == "write") {
			cin >> command;
			write_file(command);
		}
		else if (cmd == "read") {
			cin >> command;
			read_file(command);
		}
		else if (cmd == "rmfile") {
			cin >> command;
			delete_file(command);
		}
		else if (cmd == "open") {
			cin >> command;
			open_file(command);
		}
		else if (cmd == "close") {
			cin >> command;
			close_file(command);
		}
		else if (cmd == "exit") {
			save();
			break;
		}
		else cout << "无效指令,请重新输入:" << endl;
	}
	printf("Thank you for using my file system!\n");
	return 1;
}

