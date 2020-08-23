#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int minSubArrayLen(int s, vector<int>& nums) {
	int left = 0, right = 0;
	int minlen = INT_MAX;
	int sum = 0;
	while (right<nums.size())
	{
		sum += nums[right];
		while (sum >= s)
		{
			minlen = min(minlen, right-left + 1);
			sum -= nums[left];
			left++;
		}
		right++;
	}
	return minlen;
}

int main()
{
	vector<int>num;
	int n;
	int tmpin;
	int s;
	int res;
	cout << "n=";
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> tmpin;
		num.push_back(tmpin);
	}
	cout << "ÊäÈës=";
	cin >> s;
	res = minSubArrayLen(s, num);
	cout << res<<endl;

}