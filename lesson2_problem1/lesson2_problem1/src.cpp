#include<iostream>
#include<string>
#include<vector>

using namespace std;

int max(vector<int> array)
{
	int MAX = 0;
	for (unsigned i = 0; i < array.size(); ++i)
	{
		if (array[i] > MAX)
			MAX = array[i];
	}
	return MAX;
}

float max(vector<float>array)
{
	float MAX = 0;
	for (unsigned i = 0; i < array.size(); ++i)
	{
		if (array[i] > MAX)
			MAX = array[i];
	}
	return MAX;
}

string max(vector<string>array)
{
	string MAX ="\0";
	for (unsigned i = 0; i < array.size(); ++i)
	{
		if (array[i].compare(MAX)>0)
			MAX = array[i];
	}
	return MAX;
}

int max(int *array, int size)
{
	int MAX = 0;
	for (int i = 0; i < size; ++i)
	{
		if (array[i] > MAX)
			MAX = array[i];
	}
	return MAX;
}

float max(float *array, int size)
{
	float MAX = 0;
	for (int i = 0; i < size; ++i)
	{
		if (array[i] > MAX)
			MAX = array[i];
	}
	return MAX;
}

string max(string *array, int size)
{
	string MAX = "\0";
	for (int i = 0; i < size; ++i)
	{
		if (array[i].compare(MAX)>0)
			MAX = array[i];
	}
	return MAX;
}


int main()
{
	int fun;
	cout << "Please Input the array's or the vector's size:\n";
	cin >> fun;
	cout << "Please Input the Int Array's Members\n";
	int *array4=new int[fun];//随便选定大小
	for (int i = 0; i < fun; ++i)
	{
		cin >> array4[i];
	}
	cout << "Please Input the Float Array's Members\n";
	float *array5=new float[fun];
	for (int i = 0; i < fun; ++i)
	{
		cin >> array5[i];
	}
	cout << "Please Input the String Array's Members\n";
	string *array6=new string[fun];
	for (int i = 0; i < fun; ++i)
	{
		cin >> array6[i];
	}
	vector<int> array1;
	cout << "Please Input the Int Array's Members\n";
	for (int i = 0; i < fun; ++i)
	{
		int tmp;
		cin >> tmp;
		array1.push_back(tmp);
	}
	cout << "Please Input the Float Array's Members\n";
	vector<float> array2;
	for (int i = 0; i < fun; ++i)
	{
		float tmp;
		cin >> tmp;
		array2.push_back(tmp);
	}
	cout << "Please Input the String Array's Members\n";
	vector<string> array3;
	for (int i = 0; i < fun; ++i)
	{
		string tmp;
		cin >> tmp;
		array3.push_back(tmp);
	}
	
	int tmp1, tmp4;
	float tmp2, tmp5;
	string tmp3, tmp6;
	tmp1=max(array1);
	tmp2 = max(array2);
	tmp3 = max(array3);
	tmp4 = max(array4, fun);
	tmp5 = max(array5, fun);
	tmp6 = max(array6, fun);
	cout << "MAX(int)=" << tmp4 << endl;
	cout << "MAX(float)=" << showpoint<<tmp5 << endl;
	cout << "MAX(string)=" << tmp6 << endl;
	cout << "MAX(int)=" << tmp1 << endl;
	cout << "MAX(float)=" << showpoint << tmp2 << endl;
	cout << "MAX(string)=" << tmp3 << endl;
	delete[]array4;
	delete[]array5;
	delete[]array6;
}
