#include<iostream>
#include<vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* getRoot(vector<int> nums, int left, int right)
{
	if (left > right) return nullptr;
	int mid = left+(right-left) / 2;
	TreeNode* now = new TreeNode(nums[mid]);
	now->left = getRoot(nums, left, mid - 1);
	now->right = getRoot(nums, mid + 1, right);
	return now;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
	return getRoot(nums, 0, nums.size() - 1);
}

int main()
{
	int n;
	cout << "n=";
	cin >> n;
	cout << "ÊäÈëÊý×é:\n";
	vector<int> nums(n);
	for (int i = 0; i < n; ++i) cin >> nums[i];
	TreeNode* root = sortedArrayToBST(nums);
	return 0;
}