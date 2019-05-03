#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(int argc,char *argv[])
{
	
	string word="that";
	ifstream F("E:\\MJX\\C++\\lesson1_problem1\\1.txt");
	int num = 0;
	string check;
	if (!F)
	{
		cerr << "Can't Open The File!" << endl;
		return -1;
	}
	while (F >> check)
	{
		if (check == word)
			num++;
	}
	cout << "The word: that appears " << num << " times"<<endl;
	F.close();
	system("pause");
}