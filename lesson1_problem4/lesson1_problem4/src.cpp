#include<iostream>
#include<string>

using namespace std;

struct myfun
{
	int num;
	string str1;
	string str2;
};

typedef struct myfun Myfun;

int main()
{
	Myfun test;
	test.num = 10;
	test.str1 = "Hello";
	test.str2 = "World";
	cout << test.num<<endl;
	cout << test.str1 << endl;
	cout << test.str2 << endl;
	cout << "\n";
	Myfun *p;
	p = &test;
	p->num = 20;
	p->str1 = "Good";
	p->str2 = "Game";
	cout << test.num << endl;
	cout << test.str1 << endl;
	cout << test.str2 << endl;
}






