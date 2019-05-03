#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool judge(const pair<int, int> a, const pair<int, int> b)
{
	return (a.second < b.second);
}

int main()
{
	int n, k;
	int result = 0;
	int times = 0;
	vector<pair<int, int>> num;
	vector<int> RES;
	cin >> n >> k;
	int *array = new int[n+1];
	for (int i = 1; i <= n; ++i)
	{
		cin >> array[i];
		num.push_back(make_pair(i, array[i]));
	}
	sort(num.begin(), num.end(), judge);
	for (vector<pair<int, int>>::iterator iter = num.begin(); iter != num.end(); iter++)
	{
		if ((result + ((*iter).second)) <= k)
		{
			result += ((*iter).second);
			RES.push_back((*iter).first);
			times++;
		}
	}
	cout << times << endl;
	if (!times) return 0;
	else
	{
		for (unsigned int j = 0; j < RES.size(); ++j)
			cout << RES[j] << ' ';
		//delete[]array;
		return 0;
	}
}