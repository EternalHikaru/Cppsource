#include<iostream>
#include<string>

using namespace std;

string addStrings(string num1, string num2) {
	string sum;
	if (num1.empty()) return num2;
	if (num2.empty()) return num1;
	if (num1.empty() && num2.empty()) return sum;
	int len1 = num1.size(), len2 = num2.size();
	if (len1 > len2) return addStrings(num2, num1);
	for (int i = len1 - 1; i >= len1 / 2 && i >= 0; i--) swap(num1[i], num1[len1 - i - 1]);
	for (int i = len2 - 1; i >= len2 / 2 && i >= 0; i--) swap(num2[i], num2[len2 - i - 1]);
	int flag = 0;
	for (int i = 0; i < len2; i++)
	{
		if (i < len1)
		{
			int now_sum = num1[i] - '0' + num2[i] - '0' + flag;
			if (now_sum >= 10) flag = 1;
			else flag = 0;
			sum += (now_sum) % 10 + '0';
		}
		if (i >= len1)
		{
			int now_sum = num2[i] - '0'+flag;
			if (now_sum >= 10) flag = 1;
			else flag = 0;
			sum += (now_sum) % 10 + '0';
		}

	}
	if (flag) sum += '1';
	for (int i = sum.size() - 1; i >= sum.size() / 2 && i >= 0; i--) swap(sum[i], sum[sum.size() - i - 1]);
	return sum;
}

int main()
{
	string num1, num2, res;
	cout << "num1="; cin >> num1;
	cout << "num2="; cin >> num2;
	res = addStrings(num1, num2);
	cout << res;
}