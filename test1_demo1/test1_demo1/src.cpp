#include<iostream>
#include<string>

using namespace std;
int main()
{
	string phraze1("Play");
	char phraze2[]("Play");
	int num1= phraze1.size();
	int num2 = strlen(phraze2);
	cout << num1 << endl<<num2<<endl;
	
}