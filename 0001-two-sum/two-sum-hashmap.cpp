class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indexOf;
        indexOf[nums[0]] = 0;
        for (int i=1; i<nums.size(); i++) {
            if (indexOf.find(target-nums[i]) != indexOf.end()) {
                return vector<int>({indexOf[target-nums[i]], i});
            }
            indexOf[nums[i]] = i;
        }
        return {};
    }
};
