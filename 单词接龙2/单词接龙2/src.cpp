#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

bool justoneword(string a, string b)
{
	int differernt = 0;;
	for (int i = 0; i < a.size()&&differernt<2; ++i)
	{
		if (a[i] != b[i]) differernt++;
	}
	return differernt == 1;
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
	int INF = 1 << 20;
	unordered_map<string, int> s;
	vector<string> idword;
	int id = 0;
	for (const string& str : wordList)
	{
		if (!s.count(str))
		{
			s[str] = id++;
			idword.push_back(str);
		}
	}
	if (!s.count(endWord)) return {};
	if (!s.count(beginWord))
	{
		s[beginWord] = id++;
		idword.push_back(beginWord);
	}//beginWord在最后一个
	vector<vector<int>> map(idword.size());
	vector<vector<string>> result;
	for (int i = 0; i < idword.size(); ++i)
	{
		for (int j = i+1; j < idword.size(); ++j)
		{
			if (justoneword(idword[i], idword[j]))
			{
				map[i].push_back(j);
				map[j].push_back(i);
			}
		}
	}
	int destid = s[endWord];
	queue<vector<int>> q;
	vector<int> cost(id, INF);
	int beginid = s[beginWord];
	cost[beginid] = 0;
	q.push(vector<int>{beginid});//q初始化
;	while (!q.empty())
	{
		vector<int> tmpres = q.front();
		q.pop();
		int index = tmpres.back();
		if (index == destid)
		{
			vector<string> tmpstr;
			for (int i : tmpres) tmpstr.push_back(idword[i]);
			result.push_back(tmpstr);
		}
		else
		{
			for (int j = 0; j < map[index].size(); ++j)
			{
				int next = map[index][j];
				if (cost[next] >= cost[index] + 1)
				{
					cost[next] = cost[index] + 1;
					vector<int> tmp(tmpres);
					tmp.push_back(next);
					q.push(tmp);
				}
			}
		}
	}
	return result;
}

int main()
{
	string beginWord;
	string endWord;
	vector<string> wordList;
	vector<vector<string>> result;
	cout << "beginWord="; cin >> beginWord;
	cout << "endWord="; cin >> endWord;
	string tmpstr;
	while (cin >> tmpstr)
	{
		wordList.push_back(tmpstr);
	}
	result = findLadders(beginWord, endWord, wordList);
	for (int i = 0; i < result.size(); ++i)
	{
		for (int j = 0; j < result[i].size(); ++j)
		{
			cout << result[i][j] << "\t";
		}
		cout << endl;
	}
	return 0;
}