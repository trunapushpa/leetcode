class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size()-1;
        for (i = nums.size()-2; i>=0; i--) {
            if (nums[i] >= nums[i+1]) continue;
            else break;
        }
        if (i==-1) {
            sort(nums.begin(), nums.end());
            return;
        }
        int justGreaterIndex = INT_MAX;
        for (int j=i+1; j < nums.size(); j++) {
            if (nums[j] > nums[i]) {
                if (justGreaterIndex == INT_MAX) {
                    justGreaterIndex = j;
                } else {
                    if (nums[justGreaterIndex] > nums[j]) justGreaterIndex = j;
                }
            }
        }
        int a = nums[justGreaterIndex];
        nums[justGreaterIndex] = nums[i];
        nums[i] = a;
        sort(nums.begin() + i + 1, nums.end());
    }
};
