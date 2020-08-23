#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(const pair<int, int>x, const pair<int, int> y){ return x.second < y.second;}

int MaxIntervalNum(vector<pair<int,int>> a)
{
	vector<pair<int, int>> result;
	sort(a.begin(), a.end(), compare);//���������Ҷ˵��������
	int begin = a[0].second;
	result.push_back(make_pair(a[0].first, a[0].second));
	for (int i = 1; i < a.size(); ++i)
	{
		if (a[i].first >= begin)
		{
			begin = a[i].second;
			result.push_back(make_pair(a[i].first, a[i].second));
		}
	}//�ӵ�һ����ʼ(��һ���ؼ���)����,һ��������˵����֮ǰ������Ҷ˵㣬�ͽ������
	cout <<endl<< "���������Ϊ:" << result.size()<<endl;
	for (int i = 0; i < result.size(); ++i)
		cout << "��" << i + 1 << "��:(" << result[i].first << "," << result[i].second << ")\n";
	return result.size();
}

int main()
{
	vector<pair<int, int>> interval;
	int n,result,tmpa,tmpb;
	cout << "��������n=";
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cout << "��" << i + 1 << "�����䷶Χ:";
		cin >> tmpa;
		cin >> tmpb;
		interval.push_back(make_pair(tmpa, tmpb));
	}
	result = MaxIntervalNum(interval);
	return 0;
}