#include<iostream>
#include<vector>

using namespace std;

void total_sort(int max, int now,vector<int> num)
{
	if (max == now)
	{
		for (int i = 0; i < max; ++i) cout << num[i];
		cout << endl;
	}
	for (int i = now; i < max; ++i)
	{
		swap(num[i], num[now]);
		total_sort(max, now + 1, num);
		//swap(num[i], num[now]);
	}
}

int main()
{
	int maxnum;
	cout << "全排列最大值=";
	cin >> maxnum;
	vector<int> num(maxnum);
	for (int i = 1; i <= maxnum; ++i) num[i - 1] = i;
	total_sort(maxnum, 0, num);
}