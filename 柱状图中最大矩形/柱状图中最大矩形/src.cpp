#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

int largestRectangleArea_way1(vector<int>& heights) //左右边界分开算,出现多个相同值时效率极低
{
	stack<int> upstack;
	vector<int>left;
	vector<int>right;
	for (int i = 0; i < heights.size(); ++i)
	{
		if (upstack.empty()) left.push_back(-1);
		else if (heights[upstack.top()] < heights[i]) left.push_back(upstack.top());
		else
		{
			while (!upstack.empty()&&heights[upstack.top()] >= heights[i]) upstack.pop();//等号必不可少
			if (upstack.empty()) left.push_back(-1);
			else left.push_back(upstack.top());
		}
		upstack.push(i);
	}
	while (!upstack.empty()) upstack.pop();
	for (int i = heights.size() - 1; i >= 0; --i)
	{
		if (upstack.empty()) right.insert(right.begin(),heights.size()-1);
		else if (heights[upstack.top()] < heights[i]) right.insert(right.begin(),upstack.top()-1);
		else
		{
			while (!upstack.empty() && heights[upstack.top()] >= heights[i]) upstack.pop();//等号必不可少
			if (upstack.empty()) right.insert(right.begin(), heights.size() - 1);
			else right.insert(right.begin(), upstack.top() - 1);
		}
		upstack.push(i);
	}
	int maxarea = 0;
	for (int i = 0; i < left.size(); ++i)
		if (heights[i] * (right[i] - left[i]) > maxarea) maxarea = heights[i] * (right[i] - left[i]);
	return maxarea;
}

int largestRectangleArea_way2(vector<int>& heights)//合并左右边界
{
	stack<int> upstack;
	int maxarea = 0;
	heights.insert(heights.begin(), 0);//作为边界好计算
	heights.push_back(0);//作为边界好计算
	for (int i = 0; i < heights.size(); ++i)
	{
		while (!upstack.empty() && heights[i] < heights[upstack.top()])//出现比前一个低的方块时
		{
			int now = heights[upstack.top()];
			upstack.pop();
			int left = upstack.top() + 1;//前面都比它低
			int right = i-1;//后面出现一个比它低
			maxarea = max(maxarea, now * (right - left + 1));
		}
		upstack.push(i);
	}
	return maxarea;
}

int main()
{
	vector<int> heights;
	int tmp;
	int result1;
	int result2;
	while (cin >> tmp)
	{
		heights.push_back(tmp);
	}
	result1=largestRectangleArea_way1(heights);
	result2 = largestRectangleArea_way2(heights);
	cout << result1 << '\t' << result2 << endl;;
	return 0;
}