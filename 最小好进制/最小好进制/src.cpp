#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

string smallestGoodBase(string n) {//进制为k,位数为s+1
	long long num = stoll(n);
	long long res_s = num - 1;
	for (int s = 59; s >= 2; s--)
	{
		int k = pow(num, 1.0 / s);
		if (k > 1)
		{
			long long sum = 1;
			for (int i = 0; i < s; ++i) sum = k * sum + 1;
			if (sum == num)
			{
				res_s = k;
				break;
			}
		}
	}
	return to_string(res_s);
}

int main()
{
	string n, res;
	cout << "n="; cin >> n;
	res = smallestGoodBase(n);
	cout << "res=" << res;
	return 0;
}