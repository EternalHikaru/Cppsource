#include<iostream>
#include<string>

using namespace std;

int myAtoi(string str) {
	int sum = 0;
	int flag = -1;
	int i = 0;
	for (; i < str.size(); ++i)
	{
		if (str[i] == ' ') continue;
		else break;
	}
	if (i == str.size()) return 0;
	if (str[i] <= '9' && str[i] >= '0')
	{
		flag = 1;
		sum = str[i] - '0';
		i++;
	}
	for (; i < str.size(); ++i)
	{
		if (flag == -1 && str[i] == '-')
		{
			flag = 0;
			continue;
		}
		if (flag == -1 && str[i] == '+')
		{
			flag = 1;
			continue;
		}
		if (flag != -1 && (str[i] == '-' || str[i] == '+')) break;
		if (str[i]>'9'||str[i]<'0') break;
		if (sum >= INT_MAX / 10)
		{
			if (flag == 0) return INT_MIN;
			if (flag == 1) return INT_MAX;
		}
		sum = sum * 10 + str[i] - '0';
	}
	if (flag == 0) return 0 - sum;
	else return sum;
}

int main()
{
	string num;
	int res;
	cout << "num=";
	cin >> num;
	res = myAtoi(num);
	cout << res;
	return 0;

}