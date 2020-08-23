#include<iostream>
#include<string>

using namespace std;

bool patternMatching(string pattern, string value) {
	int a = 0, b = 0, p = pattern.size(), v = value.size();
	for (int i = 0; i < pattern.size(); ++i)
	{
		if (pattern[i] == 'a') a++;
		if (pattern[i] == 'b') b++;
	}
	if (!v) return p == a || p == b;
	if (!p) return v == 0;
	if (a < b)
	{
		swap(a, b);
		for (int i = 0; i < p; ++i) pattern[i] = (pattern[i] == 'a') ? 'b' : 'a';
	}//保证a>=b,使得len_a能尽快求出
	if (a == p)
	{
		if (v % a) return false;
		int len_a = v / a;
		string p_a = value.substr(0, len_a);
		for (int i = len_a; i < v; i += len_a) if (value.substr(i, len_a) != p_a) return false;
		return true;
	}
	for (int len_a = 0; len_a * a <= value.size(); ++len_a)
	{
		int len_b;
		if ((v - a * len_a) % (p - a)) continue;
		else len_b = (v - a * len_a) / (p - a);
		string p_a, p_b;
		bool j_a = false, j_b = false;
		int now = 0;
		for (int i = 0; i < p; ++i)
		{
			if (pattern[i] == 'a' && !j_a)
			{
				p_a = value.substr(now, len_a);
				j_a = true;
				now += len_a;
			}
			else if (pattern[i] == 'a')
			{
				if (p_a != value.substr(now, len_a)) break;
				else now += len_a;
			}
			if (pattern[i] == 'b' && !j_b)
			{
				p_b = value.substr(now, len_b);
				j_b = true;
				now += len_b;
			}
			else if (pattern[i] == 'b')
			{
				if (p_b != value.substr(now, len_b)) break;
				else now += len_b;
			}
		}
		if (now == v) return true;
	}
	return false;
}

int main()
{
	string pattern;
	string value;
	cout << "输入pattern:";
	cin >> pattern;
	cout << "输入value:";
	cin >> value;
	cout << patternMatching(pattern, value);
}