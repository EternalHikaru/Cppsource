#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

bool dfs(char** board, bool** visit, int row, int clo, string word, int nowword, pair<int, int> nowpoint)
{
	if (nowword == word.size())
		return true;//��board���ҵ�word
	for (int i = 0; i < 4; ++i)//4���������β���
	{
		pair<int, int> nextpoint = make_pair(nowpoint.first + dir[i][0], nowpoint.second + dir[i][1]);//��̽��һ����
		if (nextpoint.first < row && nextpoint.first >= 0 && nextpoint.second < clo && nextpoint.second >= 0 && board[nextpoint.first][nextpoint.second] == word[nowword] && visit[nextpoint.first][nextpoint.second] == false)
		{
			visit[nextpoint.first][nextpoint.second] = true;//�ҵ���һ���ַ�ʱ����ַ�
			if (dfs(board, visit, row, clo, word, nowword+1, nextpoint)) return true;//DFS�ݹ�
		}
	}
	visit[nowpoint.first][nowpoint.second] = false;//δ�ҵ������������һ���ַ�ʱ���ϻ���
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
	}//ÿ������wordʱ����ʼ��visit[][]
	queue<pair<int,int>> points;//ʹ�ö��д洢��һ����������������
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
	}//�ҵ��͵�һ����ĸ��ͬ����������
	if (!points.empty() && word.size() == 1) return true;//wordֻ��1����ĸ������board��
	if (points.empty()) return false;//wordֻ��1����ĸ��������board��
	//word������2����ĸ�����¿�ʼ�ݹ�
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
		}//ÿ�δӵ�һ���㿪ʼ��ʱ����ʼ��visit[][]
		visit[nowpoint.first][nowpoint.second] = true;
		if (dfs(board, visit, row, clo, word, 1, nowpoint)) return true;
	}
	return false;
}

int main()//���Ժ���
{
	char** board; bool** visit; int row; int clo;string word;
	bool result;
	cout << "����board������:";
	cin >> row;
	cout << "����board������:";
	cin >> clo;
	board = new char* [row];
	visit = new bool* [row];
	for (int i = 0; i < row; ++i)
	{
		board[i] = new char[clo];
		visit[i] = new bool[clo];
	}
	cout << "����board:\n";
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
		cout << "����word:(������#ʱ��������)\n";
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