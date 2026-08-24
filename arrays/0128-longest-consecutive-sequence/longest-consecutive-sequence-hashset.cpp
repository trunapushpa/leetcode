class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> hs;
        for (auto i: nums) {
            hs.insert(i);
        }
        int ans = 0;
        for (auto n: hs) {
            if (hs.find(n-1) != hs.end()) continue;
            int ct = 1;
            int i = n;
            while (hs.find(i+1) != hs.end()) {
                ct++;
                i++;
            }
            ans = max(ans, ct);
        }
        return ans;
    }
};
