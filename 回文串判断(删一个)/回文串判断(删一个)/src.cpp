#include<iostream>
#include<string>

using namespace std;

bool judge(string s, int begin, int end)
{
	while (begin < end && s[begin] == s[end])
	{
		begin++;
		end--;
	}
	if (begin >= end) return true;
	else return false;
}

bool validPalindrome(string s) {
	int i = 0;
	while (i<s.size()/2&&s[i] == s[s.size() - i - 1]) i++;
	if (i !=s.size()/2)  return (judge(s, i + 1, s.size() - i - 1) || judge(s, i, s.size() - i - 2));
	else return true;
}



int main()
{
	string s;
	cin >> s;
	bool res=validPalindrome(s);
	cout << res;
	return 0;
}