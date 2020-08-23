#include<vector>
#include<queue>
#include<iostream>

using namespace std;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

int shortestPath(vector<vector<int>>& grid, int k) {//BFS
	int row = grid.size();
	int clo = grid[0].size();
	if (k >= row + clo - 3) return row + clo - 2;//k�㹻���ֱ�ӷ������·��row+clo-2
	queue<pair<pair<int, int>, int>> PointQueue;
	vector < vector <vector<bool>>> visit(row, vector<vector<bool>>(clo, vector<bool>(k+1)));
	PointQueue.push(make_pair(make_pair(0,0),k));
	int step = 0;
	while (!PointQueue.empty())
	{
		int pointsnum = PointQueue.size();//��ǰPointsQueue�洢����һ�����ȫ���߷�
		while (pointsnum--)
		{
			pair<pair<int, int>, int> now = PointQueue.front();
			PointQueue.pop();
			int x = now.first.first;
			int y = now.first.second;
			int now_k = now.second;
			if (x == row - 1 && y == clo - 1 && now_k >= 0) return step;
			if (visit[x][y][now_k]) continue;//���ʹ�������
			visit[x][y][now_k] = 1;//�����Ƿ���
			for (int i = 0; i < 4; ++i)//�ĸ�������̽
			{
				int next_x = x + dir[i][0];
				int next_y = y + dir[i][1];
				if (next_x >= 0 && next_x < row && next_y >= 0 && next_y < clo)
				{
					if (grid[next_x][next_y]&&now_k>=1) PointQueue.push(make_pair(make_pair(next_x, next_y), now_k - 1));//���ϰ�������
					else if(!grid[next_x][next_y]) PointQueue.push(make_pair(make_pair(next_x, next_y), now_k));//���ϰ�
				}
			}
		}//����һ�����������
		step++;
	}
	return -1;
}