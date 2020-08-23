#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(const pair<int, int>x, const pair<int, int> y){ return x.second < y.second;}

int MaxIntervalNum(vector<pair<int,int>> a)
{
	vector<pair<int, int>> result;
	sort(a.begin(), a.end(), compare);//对区间以右端点进行排序
	int begin = a[0].second;
	result.push_back(make_pair(a[0].first, a[0].second));
	for (int i = 1; i < a.size(); ++i)
	{
		if (a[i].first >= begin)
		{
			begin = a[i].second;
			result.push_back(make_pair(a[i].first, a[i].second));
		}
	}//从第一个开始(第一个必加入)遍历,一旦出现左端点大于之前区间的右端点，就将其加入
	cout <<endl<< "最大区间数为:" << result.size()<<endl;
	for (int i = 0; i < result.size(); ++i)
		cout << "第" << i + 1 << "组:(" << result[i].first << "," << result[i].second << ")\n";
	return result.size();
}

int main()
{
	vector<pair<int, int>> interval;
	int n,result,tmpa,tmpb;
	cout << "总区间数n=";
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cout << "第" << i + 1 << "个区间范围:";
		cin >> tmpa;
		cin >> tmpb;
		interval.push_back(make_pair(tmpa, tmpb));
	}
	result = MaxIntervalNum(interval);
	return 0;
}