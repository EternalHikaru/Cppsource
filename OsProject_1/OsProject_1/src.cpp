#include<iostream>
#include<Windows.h>
#include<random>
#include<ctime>
#include<algorithm>

using namespace std;

#define P(S) WaitForSingleObject(S,INFINITE)
#define V(S) ReleaseSemaphore(S,1,NULL)

HANDLE Empty, Full, Mutex;

int BufferSize;
int producer_num;
int consumer_num;


//default_random_engine seed(time(NULL));
//uniform_int_distribution<DWORD> time_random(100, 1000);


struct Buffer
{
	int* Products = new int[BufferSize];
	int begin, end;
}buffer;


DWORD WINAPI producer(LPVOID p)
{
	default_random_engine seed(time(NULL));
	//uniform_int_distribution<int> pro_random(0, producer_num-1);
	uniform_int_distribution<DWORD> time_random(1, 1000);
	int pro_num = *(int*)p;
	int nowptr;
	while (cin.get()=='\n')
	{

		P(Empty);
		P(Mutex);
		nowptr = buffer.end;
		if (buffer.end < buffer.begin)
			cout << "������" << pro_num + 1 << "����������Ʒ" << nowptr << "��(��һ��)\n";
		else
			cout << "������" << pro_num + 1 << "����������Ʒ" << nowptr << "��\n";
		V(Mutex);
		buffer.end = (buffer.end + 1) % BufferSize;
		V(Full);
		//Sleep(pro_random(seed) * 5 + 100);
		Sleep(time_random(seed));
	}
	return 0;
}

DWORD WINAPI consumer(LPVOID p)
{
	default_random_engine seed(time(NULL));
	//uniform_int_distribution<int> con_random(0, consumer_num-1);
	uniform_int_distribution<DWORD> time_random(1, 1000);
	int con_num = *(int*)p;
	int nowptr;
	while (cin.get()=='\n')
	{
		P(Full);
		P(Mutex);
		nowptr = buffer.begin;
		buffer.begin = (buffer.begin + 1) % BufferSize;
		cout << "������" << con_num+1 << "�������Ѳ�Ʒ" << nowptr << "��\n";
		V(Mutex);
		V(Empty);
		//Sleep(con_random(seed) * 100 + 100);
		Sleep(time_random(seed));
	}
	return 0;
}

int main()
{
	cout << "�����뻺��������:"; std::cin >> BufferSize;
	cout << "��������������Ŀ:"; std::cin >> producer_num;
	cout << "��������������Ŀ:"; std::cin >> consumer_num;
	HANDLE *TotalThread=new HANDLE[producer_num + consumer_num];
	Empty = CreateSemaphore(NULL, BufferSize, BufferSize, NULL);
	Full = CreateSemaphore(NULL, 0, BufferSize, NULL);
	Mutex = CreateSemaphore(NULL, 1, 1, NULL);
	if (!Empty || !Full || !Mutex)
	{
		cerr << "Failed To Create Semaphore\n";
		exit(-1);
	}
	
	for (int i = 0; i < consumer_num; ++i)
	{
		TotalThread[i] = CreateThread(NULL, 0, consumer, &i, 0,0);
		if (TotalThread[i]) WaitForSingleObject(TotalThread[i], 10);
		cout << "������" << i + 1 << "�ž�λ��\n";
	}
	cout << "������ȫ����λ��\n";

	cout << "������ȫ����λ��\n";
	for (int i = 0; i < producer_num; ++i)
	{
		TotalThread[i+consumer_num] = CreateThread(NULL, 0, producer, &i, 0, 0);
		if (TotalThread[i+consumer_num]) WaitForSingleObject(TotalThread[i+consumer_num], 10);
	}

	/*while (1)
	{

        default_random_engine seed(time(NULL));
		uniform_int_distribution<int> con_random(0, consumer_num-1);
		uniform_int_distribution<int> pro_random(0, producer_num-1);
        //uniform_int_distribution<DWORD> time_random(100, 1000);
		uniform_int_distribution<int> choose(0, 1);
		if(choose(seed))
		WaitForSingleObject(TotalThread[pro_random(seed)], INFINITE);
		else
		WaitForSingleObject(TotalThread[con_random(seed)+producer_num], INFINITE);
	}*/

	WaitForMultipleObjects(consumer_num + producer_num, TotalThread, true, INFINITE);

	return 0;
}
