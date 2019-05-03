#include<iostream>
#include<vector>

using namespace std;

int main()
{
	vector<float>array;
	float tmp;
	for (int i = 0; i < 25; ++i)
	{
		cin >> tmp;
		array.push_back(tmp);
	}
	for (int k = 0; k < 25; ++k)
	{
		cout << " "<<array[k]<<" ";
	}
	cout << "\n";
	for (int r = 0; r < 25; ++r)
	{
		array[r] = array[r] * array[r];
	}
	for (int t = 0; t < 25; ++t)
	{
		cout <<" "<< array[t]<<" ";
	}



}