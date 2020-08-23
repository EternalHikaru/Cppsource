#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

int respace(vector<string>& dictionary, string sentence) {
	vector<vector<int>> mydic(sentence.size());
	vector<int> dp(sentence.size() + 1, 0);
	dp[0] = 0;
	for (int i = 0; i < dictionary.size(); ++i)
	{
		int pos = -1;
		while ((pos = sentence.find(dictionary[i], pos + 1)) != string::npos)
			mydic[pos].push_back(dictionary[i].size());
	}
	for (int i = sentence.size() - 1; i >= 0; --i)
	{
		dp[i] = dp[i + 1] + 1;
		for (auto& x : mydic[i]) dp[i] = min(dp[i], dp[i + x]);
	}
	return dp[0];
}

int main()
{
	int n;
	int res;
	cout << "n="; cin >> n;
	vector<string> dictionary;
	string sentence;
	cout << "sentence="; cin >> sentence;
	for (int i = 0; i < n; ++i)
	{
		string tmpstr;
		cout << "dictionary[" << i << "]=";
		cin >> tmpstr;
		dictionary.push_back(tmpstr);

	}
	res = respace(dictionary, sentence);
	cout << "res="<<res;
	return 0;

}