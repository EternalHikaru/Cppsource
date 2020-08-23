#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

bool dfs(char** board, bool** visit, int row, int clo, string word, int nowword, pair<int, int> nowpoint)
{
	if (nowword == word.size())
		return true;//在board中找到word
	for (int i = 0; i < 4; ++i)//4个方向依次查找
	{
		pair<int, int> nextpoint = make_pair(nowpoint.first + dir[i][0], nowpoint.second + dir[i][1]);//试探下一个点
		if (nextpoint.first < row && nextpoint.first >= 0 && nextpoint.second < clo && nextpoint.second >= 0 && board[nextpoint.first][nextpoint.second] == word[nowword] && visit[nextpoint.first][nextpoint.second] == false)
		{
			visit[nextpoint.first][nextpoint.second] = true;//找到下一个字符时标记字符
			if (dfs(board, visit, row, clo, word, nowword+1, nextpoint)) return true;//DFS递归
		}
	}
	visit[nowpoint.first][nowpoint.second] = false;//未找到符合情况的下一个字符时向上回溯
	return false;
}

bool FindWord(char** board, bool** visit, int row, int clo,string word)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < clo; ++j)
		{
			visit[i][j] = false;
		}
	}//每次输入word时均初始化visit[][]
	queue<pair<int,int>> points;//使用队列存储第一个符合条件的坐标
	int nowword = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < clo; ++j)
		{
			if (board[i][j] == word[0] && visit[i][j] == false)
			{
				points.push(make_pair(i, j));
			}
		}
	}//找到和第一个字母相同的所有坐标
	if (!points.empty() && word.size() == 1) return true;//word只有1个字母，且在board中
	if (points.empty()) return false;//word只有1个字母，但不在board中
	//word有至少2个字母，由下开始递归
	while (!points.empty())
	{
		pair<int, int> nowpoint = points.front();
		points.pop();
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < clo; ++j)
			{
				visit[i][j] = false;
			}
		}//每次从第一个点开始找时均初始化visit[][]
		visit[nowpoint.first][nowpoint.second] = true;
		if (dfs(board, visit, row, clo, word, 1, nowpoint)) return true;
	}
	return false;
}

int main()//测试函数
{
	char** board; bool** visit; int row; int clo;string word;
	bool result;
	cout << "输入board的行数:";
	cin >> row;
	cout << "输入board的列数:";
	cin >> clo;
	board = new char* [row];
	visit = new bool* [row];
	for (int i = 0; i < row; ++i)
	{
		board[i] = new char[clo];
		visit[i] = new bool[clo];
	}
	cout << "输入board:\n";
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < clo; ++j)
		{
			cin >> board[i][j];
			visit[i][j] = false;
		}
	}
	while (1)
	{
		cout << "输入word:(当输入#时结束测试)\n";
		cin >> word;
		if (word == "#") break;
		result = FindWord(board, visit, row, clo, word);
		if (result)
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	return 0;
}