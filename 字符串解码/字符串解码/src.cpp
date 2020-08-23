#include<iostream>
#include<string>
#include<vector>

using namespace std;

string decodeString(string& s) {
	vector<pair<int,pair<int,int>>> data;//(data,pos(begin,end)) begin=第一个数字pos||end='['pos
	for (int i = 0; i < s.size();)
	{
		if (s[i] - '0' >= 0 && s[i] - '9' <= 0)
		{
			int j;
			int tmpnum=s[i]-'0';
			for (j = i+1; j < s.size(); ++j)
			{
				if (s[j] == '[') break;
				if(s[j]-'0'>=0&&s[j]-'9'<=0)
				tmpnum = tmpnum * 10 + s[j] - '0';
			}
			data.push_back(make_pair(tmpnum, make_pair(i, j)));
			i = j;
		}
		else i++;
	}
	for (int i = data.size()-1; i >=0; i--)
	{
		for (int j = data[i].second.second; j < s.size(); ++j)
		{
			if (s[j] == ']')
			{
				string tmpstr = s.substr(data[i].second.second + 1, j-data[i].second.second-1);
				string tmprepeat;
				string tmpok;
				for (int p = 0; p < data[i].first; ++p)
				{
					tmprepeat.append(tmpstr);
				}
				tmpok = s.substr(0, data[i].second.first) + tmprepeat + s.substr(j + 1, s.size()-j-1);
				s = tmpok;
				break;
			}
		}
	}
	return s;
}

int main()
{
	string s;
	string result;
	cin >> s;
	result=decodeString(s);
	cout << result;
}