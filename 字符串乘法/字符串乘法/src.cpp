#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

string multiply(string num1, string num2) {
	if (num1 == "0" || num2 == "0") return "0";
	string res;
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	vector<int> num(num1.size() + num2.size() + 1);
	for (int i = 0; i < num2.size(); ++i)
	{
		for (int j = 0; j < num1.size(); ++j)
		{
			int mul = (num2[i] - '0') * (num1[j] - '0');
			num[i + j] += mul;
		}
	}
	int plus = 0;
	for (int i = 0; i < num.size(); ++i)
	{
		int tmp = num[i];
		num[i] = (plus + tmp) % 10;
		plus = (plus + tmp) / 10;
	}
	int flag = 0;
	for (int i = num.size() - 1; i >= 0; i--)
	{
		if (!flag && !num[i]) continue;
		if (num[i]) flag = 1;
		res += num[i] + '0';
	}
	return res;
}

int main()
{
	string num1,num2,res;
	cout << "num1="; cin >> num1;
	cout << "num2="; cin >> num2;
	res = multiply(num1, num2);
	cout << "res=" << res;
}