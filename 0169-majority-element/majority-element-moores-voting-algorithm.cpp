class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majorityElement = nums[0];
        int majorityCount = 1;
        for (int i=1; i<nums.size(); i++) {
            if (nums[i] == majorityElement) {
                majorityCount++;
            } else {
                majorityCount--;
            }
            if (majorityCount == 0) {
                majorityElement = nums[i];
                majorityCount = 1;
            }
        }
        return majorityElement;
    }
};
