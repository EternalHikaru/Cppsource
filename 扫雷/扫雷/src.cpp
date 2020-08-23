#include<iostream>
#include<vector>

using namespace std;

int dir[8][2] = {
		{-1,0},
		{-1,1},
		{0,1},
		{1,1},
		{1,0},
		{1,-1},
		{0,-1},
		{-1,-1}
};
void dfs(vector<vector<char>>& board, int x, int y)
{
	int row = board.size(), clo = board[0].size();
	int mine_num = 0;
	for (int i = 0; i < 8; ++i)
	{
		int newx = x + dir[i][0], newy = y + dir[i][1];
		if (newx < 0 || newx >= row || newy < 0 || newy >= clo) continue;
		mine_num += board[newx][newy] == 'M';
	}
	if (mine_num) board[x][y] = '0' + mine_num;
	else {
		board[x][y] = 'B';
		for (int i = 0; i < 8; ++i)
		{
			int newx = x + dir[i][0], newy = y + dir[i][1];
			if (newx < 0 || newx >= row || newy < 0 || newy >= clo||board[newx][newy]!='E') continue;
			dfs(board, newx, newy);
		}
	}
}

vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
	if (click.empty() || board.empty()) return board;
	int x = click[0], y = click[1];
	if (board[x][y] == 'M') board[x][y] = 'X';
	else dfs(board, x, y);
	return board;
}

int main()
{
	
	vector<int> click(2);
	int row, clo;
	cout << "row="; cin >> row;
	cout << "clo="; cin >> clo;
	vector<vector<char>> board(row,vector<char>(clo));
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < clo; ++j)
			cin >> board[i][j];
	}
	cout << "click=";
	for (int i = 0; i < 2; ++i) cin >> click[i];
	updateBoard(board, click);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < clo; ++j)
			cout<< board[i][j]<<" ";
		cout << endl;
	}
}