#include<iostream>
#include<algorithm>

using namespace std;

int d(string a, string b)
{
	int** table = new int* [a.size()+1];
	for (int i = 0; i < a.size() + 1; ++i)
	{
		table[i] = new int[b.size() + 1];
		for (int j = 0; j < b.size() + 1; ++j)//table[i][j]代表从a[i]转换到b[j]的编辑距离
		{
			table[i][j] = a.size()+b.size();//初始化，设为最大值(a.size()+b.size())已足够
			table[0][j] = j;//a为空，增加次数
		}
		table[i][0] = i;//b为空，删除次数
	}
	for (int i = 1; i <= a.size(); ++i)
	{
		for (int j = 1; j <= b.size(); ++j)
		{
			int tmp;
			if (a[i-1] == b[j-1]) tmp = 0;
			else tmp = 1;
			table[i][j] = min(table[i][j - 1] + 1, min(table[i - 1][j] + 1, table[i - 1][j - 1] + tmp));//三种情况的最小值
			//table[i][j-1]+1为加上b[b.size()-1]
			//table[i-1][j]+1为删除a[i]
			//table[i-1][j-1]+tmp为改变操作，若相同则不需要操作
		}
	}//时间复杂度为O(a.size()*b.size())
	return table[a.size()][b.size()];
}


int main()
{
	string A, B;
	cout << "输入字符串A=";
	cin >> A;
	cout << "输入字符串B=";
	cin >> B;
	cout << "d(A,B)="<<d(A,B)<<endl;
	return main();
}