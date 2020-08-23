#include<iostream>
#include<algorithm>

using namespace std;

int d(string a, string b)
{
	int** table = new int* [a.size()+1];
	for (int i = 0; i < a.size() + 1; ++i)
	{
		table[i] = new int[b.size() + 1];
		for (int j = 0; j < b.size() + 1; ++j)//table[i][j]�����a[i]ת����b[j]�ı༭����
		{
			table[i][j] = a.size()+b.size();//��ʼ������Ϊ���ֵ(a.size()+b.size())���㹻
			table[0][j] = j;//aΪ�գ����Ӵ���
		}
		table[i][0] = i;//bΪ�գ�ɾ������
	}
	for (int i = 1; i <= a.size(); ++i)
	{
		for (int j = 1; j <= b.size(); ++j)
		{
			int tmp;
			if (a[i-1] == b[j-1]) tmp = 0;
			else tmp = 1;
			table[i][j] = min(table[i][j - 1] + 1, min(table[i - 1][j] + 1, table[i - 1][j - 1] + tmp));//�����������Сֵ
			//table[i][j-1]+1Ϊ����b[b.size()-1]
			//table[i-1][j]+1Ϊɾ��a[i]
			//table[i-1][j-1]+tmpΪ�ı����������ͬ����Ҫ����
		}
	}//ʱ�临�Ӷ�ΪO(a.size()*b.size())
	return table[a.size()][b.size()];
}


int main()
{
	string A, B;
	cout << "�����ַ���A=";
	cin >> A;
	cout << "�����ַ���B=";
	cin >> B;
	cout << "d(A,B)="<<d(A,B)<<endl;
	return main();
}