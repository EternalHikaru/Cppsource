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

const char* myfilepath = "./myfile";/*��������*/
const int BLOCKSIZE = 256;       //�̿��С
const int MAXOPEN = 5;          //�ܴ������ļ���
const int BLOCKNUM = 64;   //�̿���
const int DISKSIZE = BLOCKSIZE * BLOCKNUM;    //���̴�С

typedef struct FCB {
	char fcb_name[FCBNAMELEN];
	SIZE size;
	TYPE type;
	ID father_block_id;//������
	ID block_id;//��ǰ���
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
			}//��һ��ΪĿ¼��
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
	dirFile root;//��Ŀ¼
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
char* BaseAddress;//������ռ�Ļ���ַ
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
	cout << "��ʽ���ɹ�" << endl;
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
				cout << "���ļ����ڴ��б��У���ϵͳֻ�ܸ�д��ǰĿ¼�µ��ļ�" << endl;
				return false;
			}
		}
	}
	if (pos == MAXOPEN)
	{
		cout << "���ļ���δ�򿪣����ȴ���д���ļ�" << endl;
		return false;
	}
	int now_pos = pos;
	ID file_start_id = openlist->fcb[now_pos].block_id - 3;
	begin_pos = osPointer->data[file_start_id];
	end_pos = osPointer->data[file_start_id + 1];
	cout << "�������ı���Ctrl+D����" << endl;
	//memset(begin_pos, 4, sizeof(char) * BLOCKSIZE);//��Ϊ�ؼ�������֮ǰ�ַ����飬��ֹ�޸�ʧЧ
	char input;
	while (((input = getchar()) != 4)) {
		if (begin_pos < end_pos - 1) {
			*begin_pos++ = input;
		}
		else {
			cout << "�ﵽ�����ļ����������";
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
				cout << "��ϵͳֻ�ܶ�ȡ��ǰĿ¼���ļ�" << endl;
				return false;
			}
		}
	}
	if (pos == MAXOPEN)
	{
		cout << "���ļ���δ�򿪣���򿪺��ٶ�ȡ��Ϣ" << endl;
		return false;
	}

	int now_pos = pos;
	ID  file_start_id = openlist->fcb[now_pos].block_id - 3;
	char* begin_pos = osPointer->data[file_start_id];
	char* end_pos = osPointer->data[file_start_id + 1];
	cout << "�ļ�����Ϊ:" << endl;
	while ((*begin_pos) != 4 && (begin_pos < end_pos))
	{
		//���read
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
			cout << "���ļ��ѱ���" << endl;
			return false;
		}
	}
	if (openlist->open_num == MAXOPEN)
	{
		cout << "���ļ���Ŀ�ﵽ����" << endl;
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
		cout << "��ǰĿ¼�²����ڸ��ļ�" << endl;
		return false;
	}
	openlist->fcb[now_openfile_num] = nowdir->fcb[fcb_pos];
	openlist->open_num++;
	now_openfile_num++;
	cout << "�ļ��򿪳ɹ�" << endl;
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
				cout << "���ļ��Ѵ򿪣������ڵ�ǰĿ¼�£��޷��ر�" << endl;
				return false;
			}
		}
	}
	if (pos == MAXOPEN)
	{
		cout << "���ļ����ڴ��б�,����Ҫ�ر�" << endl;
		return false;
	}
	openlist->open_num--;
	openlist->fcb[pos].fcb_init();
	now_openfile_num--;
	cout << "���ļ��ѹر�" << endl;
	return true;
}
void  mkdir(char* name)
{
	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);
	for (int i = 1; i < MAXFCBNUM; ++i)//���ͬһĿ¼�Ƿ����ͬ���ļ���
	{
		if (nowdir->fcb[i].type == FOLDER && strcmp(nowdir->fcb[i].fcb_name, name) == 0)
		{
			cout << "���ļ����´���ͬ���ļ���" << endl;
			return;
		}
	}
	int pos;
	for (pos = 1; pos < MAXFCBNUM; ++pos)//�����Ƿ���ڿհ�fcb
	{
		if (nowdir->fcb[pos].type == EMPTY) break;
	}
	if (pos == MAXFCBNUM)
	{
		cout << "��Ŀ¼��������ѡ���µ�Ŀ¼�´���" << endl;
		return;
	}
	ID now_fcb_pos = pos;
	int j;
	for (j = 3; j < BLOCKNUM; ++j)//�����Ƿ���ڿյ�Ӳ�̿�
	{
		if (osPointer->FAT1[j] == 0) break;
	}
	if (j == BLOCKNUM)
	{
		cout << "Ӳ������" << endl;
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
	cout << "������Ŀ¼�ɹ�" << endl;
	return;
}
void rmdir(char* name)
{
	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);

	int pos;
	for (pos = 1; pos < MAXFCBNUM; ++pos)//���ͬһĿ¼�Ƿ����ͬ���ļ�
	{
		if (nowdir->fcb[pos].type == FOLDER && strcmp(nowdir->fcb[pos].fcb_name, name) == 0)
			break;
	}
	ID find_fcb_pos = pos;
	if (find_fcb_pos == MAXFCBNUM)
	{
		cout << "��ǰĿ¼�²����ڸ���Ŀ¼" << endl;
		return;
	}
	ID id = nowdir->fcb[find_fcb_pos].block_id;
	dirFile* sonDir;
	sonDir = (dirFile*)(osPointer->data[id - 3]);
	for (int i = 1; i < MAXFCBNUM; ++i)
	{
		if (sonDir->fcb[i].type != EMPTY)
		{
			cout << "���ļ��зǿգ�����ɾ���ļ��������ݲ���" << endl;
			return;
		}
	}
	osPointer->FAT1[id] = osPointer->FAT2[id] = 0;//FAT���
	char* x = osPointer->data[id - 3];
	memset(x, 0, BLOCKSIZE);
	nowdir->fcb[find_fcb_pos].fcb_init();
	cout << "ɾ����ǰĿ¼�µ��ļ��гɹ�" << endl;
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
			cout << "�޷���ͬһĿ¼�´���ͬ���ļ�" << endl;
			return;
		}
	}
	if (!empty_num)
	{
		cout << "�Ѿ��ﵽĿ¼���������ޣ��޷�������Ŀ¼" << endl;
		return;
	}

	int pos;
	for (pos = 3; pos < BLOCKNUM; ++pos)//����FATѰ�ҿհ��������ڷ�����̿��
	{
		if (osPointer->FAT1[pos] == 0) break;
	}
	if (pos == BLOCKNUM)
	{
		cout << "��������" << endl;
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
	cout << "�ڵ�ǰĿ¼�´����ı��ļ��ɹ�" << endl;
	return;
}
void delete_file(char* name)
{
	dirFile* nowdir;
	if (now_block_id == 2) nowdir = &(osPointer->root);
	else nowdir = (dirFile*)(osPointer->data[now_block_id - 3]);
	int i;
	for (i = 1; i < BLOCKNUM; ++i)//���ļ�
	{
		if (nowdir->fcb[i].type == ROUTINE && strcmp(nowdir->fcb[i].fcb_name, name) == 0)
			break;
	}
	if (i == BLOCKNUM)
	{
		cout << "��ǰĿ¼�²����ڸ��ļ�" << endl;
		return;
	}

	int j;
	for (j = 0; j < MAXOPEN; ++j)//�ҵ�ǰ�򿪵��ļ�
	{
		if (openlist->fcb[j].type == ROUTINE && strcmp(openlist->fcb[j].fcb_name, name) == 0)
		{
			if (openlist->fcb[j].father_block_id == now_block_id) break;
			else
			{
				cout << "���ļ�δ�ڵ�ǰĿ¼��" << endl;
				return;
			}
		}
	}
	if (j != MAXOPEN) close_file(name);//ɾ��ر��ļ�

	int now_fcb_pos = i;
	int id = nowdir->fcb[now_fcb_pos].block_id;
	osPointer->FAT1[id] = osPointer->FAT2[id] = 0;
	char* x = osPointer->data[id - 3];
	memset(x, 0, BLOCKSIZE);
	nowdir->fcb[now_fcb_pos].fcb_init();
	cout << "ɾ���ɹ�" << endl;
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
			cout << nowdir->fcb[i].fcb_name << "\t�ı��ļ�" << endl;
		}
		if (nowdir->fcb[i].type == FOLDER)
		{
			folder_count++;
			cout << nowdir->fcb[i].fcb_name << "\t�ļ���" << endl;
		}
	}
	cout << "\n��Ŀ¼�¹���" << file_count << "���ı��ļ�," << folder_count << "���ļ���" << endl;
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
			cout << "��ǰĿ¼��Ϊ��Ŀ¼" << endl;
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
		cout << "�����ڸ�Ŀ¼" << endl;
		return false;
	}
	now_block_id = nowdir->fcb[pos].block_id;
	currentPath = currentPath + nowdir->fcb[pos].fcb_name + "\\";
	cout << "���뵱ǰĿ¼�µ���Ŀ¼�ɹ�" << endl;
	return true;
}
void save() {
	fp = fopen(myfilepath, "w+");
	fwrite(BaseAddress, sizeof(char), DISKSIZE, fp);
	fclose(fp);
	//�ͷ��ڴ��ϵ��������
	free(osPointer);
	//�ͷ��û����ļ���
	delete openlist;
	cout<<"�˳��ļ�ϵͳ�ɹ���\n\n";
	return;
}


int main()
{
	printf("/**************   ������ʹ�ý��ܣ�   *************\\\n");
	printf("/**************   mkfile: �����ļ�   *************\\\n");
	printf("/**************   mkdir:�����ļ���   *************\\\n");
	printf("/**************   rmfile: ɾ���ļ�   *************\\\n");
	printf("/**************   rmdir:ɾ���ļ���   *************\\\n");
	printf("/**************   cd  :   ����·��   *************\\\n");
	printf("/**************   dir:��ʾ��ǰ·������   *********\\\n");
	printf("/**************   open:   ���ļ�   *************\\\n");
	printf("/**************   close:  �ر��ļ�   *************\\\n");
	printf("/**************   read:     ���ļ�   *************\\\n");
	printf("/**************   write:    д�ļ�   *************\\\n");
	printf("/**************   format:   ��ʽ��   *************\\\n");
	printf("/**************   exit:       �˳�   *************\\\n");
	openlist = new NOWOPENLIST;//�����û��ļ��򿪱�
	BaseAddress = (char*)malloc(DISKSIZE);//��������ռ䲢�ҳ�ʼ��
	osPointer = (DISK*)(BaseAddress);//������̳�ʼ��	
	if ((fp = fopen(myfilepath, "r")) != NULL) {//���ش����ļ�
		fread(BaseAddress, sizeof(char), DISKSIZE, fp);
		printf("���ش����ļ�( %s )�ɹ�,���ڿ��Խ��в�����!\n\n", myfilepath);
	}
	else {
		printf("�������һ��ʹ�ø��ļ�����ϵͳ!\t���ڳ�ʼ��...\n");
		Format();
		printf("��ʼ���Ѿ����,���ڿ��Խ��в�����!\n\n");
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
		else cout << "��Чָ��,����������:" << endl;
	}
	printf("Thank you for using my file system!\n");
	return 1;
}

