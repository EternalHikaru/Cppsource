#include<iostream>
#include<string>

using namespace std;

void modify(string *str)
{
	*str = "well play *";
}
void modify(string &str)
{
	str = "well play &";
}
int main()
{
	string word = "Good Game!";
	cout << "Good Game!=" << word<<endl;
	modify(&word);
	cout << "Good Game!=" << word << endl;
	modify(word);
	cout << "Good Game!=" << word << endl;
}