#include<iostream>
#include<vector>
#include<random>
#include<ctime>

using namespace std;

int getpivot(vector<int>& num, int left, int right)
{
	if (left == right) return left;
	default_random_engine e(time(NULL));
	uniform_int_distribution<unsigned> u(left, right);
	int random_index = u(e);
	int pivot = num[random_index];
	swap(num[left], num[random_index]);
	int begin = left;
	//int end = right;
	//while (begin < end)
	{
		//while (begin < end && pivot > num[end]) end--;
		//if (begin < end) num[begin] = num[end];
		//while (begin < end && pivot < num[begin]) begin++;
		//if (begin < end) num[end] = num[begin];
		
	}
	for (int i = begin + 1; i <= right; ++i) if (num[i] > pivot) swap(num[i], num[++begin]);
	//num[begin] = pivot;
	swap(num[begin], num[left]);
	return begin;
}

int quicksort(vector<int>& num, int left, int right, int index)//½µÐò
{
	int now = getpivot(num, left, right);
	if (now + 1 == index) return num[now];
	else return now + 1 < index ? quicksort(num, now + 1, right, index) : quicksort(num, left, now - 1, index);
}

int findKthLargest(vector<int>& nums, int k) {
	return quicksort(nums, 0, nums.size() - 1, k);
}

int main()
{
	int n, k;
	cout << "n=";
	cin >> n;
	cout << "Êý×éÎª:\n";
	vector<int> nums(n);
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		nums[i] = tmp;
	}
	cout << "k=";
	cin >> k;
	cout<<findKthLargest(nums, k);
	return 0;

}