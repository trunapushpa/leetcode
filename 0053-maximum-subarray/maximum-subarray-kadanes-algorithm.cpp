class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int leastTillNow = nums[0];
        int sumSoFar = nums[0];
        int maxAns = nums[0];
        for (int i=1; i<nums.size(); i++) {
            sumSoFar += nums[i];
            if (sumSoFar - leastTillNow > maxAns){
                maxAns = sumSoFar - leastTillNow;
            }
            if (sumSoFar > maxAns) {
                maxAns = sumSoFar;
            }
            if (sumSoFar < leastTillNow) {
                leastTillNow = sumSoFar;
            }
        }
        return maxAns;
    }
};
