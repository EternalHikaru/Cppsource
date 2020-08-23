#include<iostream>
#include<vector>

using namespace std;

/*滚动数组优化*/
/*
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	vector<int> dp(n);
	dp[0] = (obstacleGrid[0][0] == 0);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (obstacleGrid[i][j] == 1)
			{
				dp[j] = 0;
				continue;
			}
			if (j > 0 && obstacleGrid[i][j] == 0) dp[j] += dp[j - 1];
		}
	}
	return dp.back();
}
*/

/*二维数组，常规dp*/
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	vector<vector<int>> dp(m,vector<int>(n));
	dp[0][0] = (obstacleGrid[0][0] == 0);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (obstacleGrid[i][j] == 1) dp[i][j] = 0;
			if (obstacleGrid[i][j] == 0)
			{
				if (i > 0 && j > 0) dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				else if (i > 0) dp[i][j] = dp[i - 1][j];
				else if (j > 0)dp[i][j] = dp[i][j - 1];
			}
		}
	}
	return dp[m-1][n-1];
}



int main()
{
	int m, n, result;
	cout << "m="; cin >> m;
	cout << "n="; cin >> n;
	vector<vector<int>> maze(m,vector<int>(n));
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
			cin >> maze[i][j];
	}
	result = uniquePathsWithObstacles(maze);
	cout << result;
	return 0;
}