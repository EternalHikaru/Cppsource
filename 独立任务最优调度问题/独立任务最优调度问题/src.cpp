#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

int MinTime(vector<int> a, vector<int> b)
{
	int total_a = 0;
	for (int i = 0; i < a.size(); ++i) total_a += a[i];//求出只用a处理的总时间（也可用b），相当于总背包重量
	int** table = new int* [b.size()+1];
	for (int i = 0; i < b.size() + 1; ++i)
	{
		table[i] = new int[total_a + 1];//建表，类似背包问题
		for (int j = 0; j < total_a + 1; ++j) table[i][j] = 0;//初始化
	}
	//table[i][j]相当于完成前i个作业a机器花j时间时b机器要花的时间
	int sum_a = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		sum_a += a[i];
		for (int j = 0; j <= sum_a; ++j)
		{
			table[i + 1][j] = table[i][j] + b[i];//该任务以a当前时间无法完成，故让b完成
			if (j >= a[i]) table[i + 1][j] = min(table[i][j] + b[i], table[i][j - a[i]]);
			//该任务以a当前时间可以完成，考虑a与b两者谁完成的时间更少
		}
	}
	int absAtoB = INT_MAX;
	int time_a = 0;
	int time_b = 0;
	for (int i = 0; i <= total_a; ++i)
	{
		if (abs(i - table[b.size()][i]) < absAtoB)
		{
			absAtoB = abs(i - table[b.size()][i]);
			time_a = i;
			time_b = table[b.size()][i];
		}
	}//找到A与B相差时间最小的方案	
	return max(time_a,time_b);//返回该方案的较大时间
}


int main()
{
	vector<int>A;
	vector<int>B;
	int n,tmp,result;
	cout << "输入作业个数n=";
	cin >> n;
	cout << "输入A[]:\n";
	for (int i = 0; i < n; ++i)
	{
		cin >> tmp;
		A.push_back(tmp);
	}
	cout << "输入B[]:\n";
	for (int i = 0; i < n; ++i)
	{
		cin >> tmp;
		B.push_back(tmp);
	}
	result = MinTime(A, B);
	cout << "MinTime=" << result << endl;
	return 0;
}