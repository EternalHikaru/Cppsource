#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

int MinTime(vector<int> a, vector<int> b)
{
	int total_a = 0;
	for (int i = 0; i < a.size(); ++i) total_a += a[i];//���ֻ��a�������ʱ�䣨Ҳ����b�����൱���ܱ�������
	int** table = new int* [b.size()+1];
	for (int i = 0; i < b.size() + 1; ++i)
	{
		table[i] = new int[total_a + 1];//�������Ʊ�������
		for (int j = 0; j < total_a + 1; ++j) table[i][j] = 0;//��ʼ��
	}
	//table[i][j]�൱�����ǰi����ҵa������jʱ��ʱb����Ҫ����ʱ��
	int sum_a = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		sum_a += a[i];
		for (int j = 0; j <= sum_a; ++j)
		{
			table[i + 1][j] = table[i][j] + b[i];//��������a��ǰʱ���޷���ɣ�����b���
			if (j >= a[i]) table[i + 1][j] = min(table[i][j] + b[i], table[i][j - a[i]]);
			//��������a��ǰʱ�������ɣ�����a��b����˭��ɵ�ʱ�����
		}
	}
	int absAtoB = INT_MAX;
	int time_a = 0;
	int time_b = 0;
	for (int i = 0; i <= total_a; ++i)
	{
		if (abs(i - table[b.size()][i]) < absAtoB)
		{
			absAtoB = abs(i - table[b.size()][i]);
			time_a = i;
			time_b = table[b.size()][i];
		}
	}//�ҵ�A��B���ʱ����С�ķ���	
	return max(time_a,time_b);//���ظ÷����Ľϴ�ʱ��
}


int main()
{
	vector<int>A;
	vector<int>B;
	int n,tmp,result;
	cout << "������ҵ����n=";
	cin >> n;
	cout << "����A[]:\n";
	for (int i = 0; i < n; ++i)
	{
		cin >> tmp;
		A.push_back(tmp);
	}
	cout << "����B[]:\n";
	for (int i = 0; i < n; ++i)
	{
		cin >> tmp;
		B.push_back(tmp);
	}
	result = MinTime(A, B);
	cout << "MinTime=" << result << endl;
	return 0;
}