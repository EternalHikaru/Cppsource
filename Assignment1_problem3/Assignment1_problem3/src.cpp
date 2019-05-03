#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int main()
{
	int n;
	string tmpname;
	int tmpscore;
	int max = -2000000;
	int min = 2000000;
	int TMP;
	cin >> n;
	vector<pair<string, int>> tmp;
	vector<pair<string, pair<int,int>>> result;
	for (int i = 0; i < n; ++i)
	{
		cin >> tmpname;
		cin >> tmpscore;
		tmp.push_back(make_pair(tmpname, tmpscore));
	}
	for (int j = 0; j < n; ++j)
	{
		
		int bool1 = 1;
		for (int k = 0; k < result.size(); ++k)
		{
			if (tmp[j].first == result[k].first)
			{
				(result[k].second).first += tmp[j].second;
				if(tmp[j].second > 0)
				(result[k].second).second = j;
				bool1 = 0;
				break;
			}
		}
		if(bool1)
		result.push_back(make_pair(tmp[j].first, make_pair(tmp[j].second, j)));
	}
	for (int t = 0; t < result.size(); ++t)
	{
		if (((result[t].second).first)>max)
		{
			max = ((result[t].second).first);
			min = ((result[t].second).second);
			TMP = t;
		}
		if(((result[t].second).first)==max)
		{
			if (((result[t].second).second) < min)
			{
				min = ((result[t].second).second);
				TMP = t;
			}
		}
	}
	cout << result[TMP].first<<endl;
	return 0;
	
}