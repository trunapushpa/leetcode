class Solution {
private:
    void swap(vector<int>& nums, int i, int j){
        int a = nums[i];
        nums[i] = nums[j];
        nums[j] = a;
    }
public:
    void sortColors(vector<int>& nums) {
        // 0 - low-1
        // low - mid-1
        // mid - high-1 unsorted
        // high - n-1
        int low = 0, mid = 0, high = nums.size();
        while(mid<high) {
            if (nums[mid]==0) {
                swap(nums, low, mid);
                low++;
                mid++;
            } else if (nums[mid]==1) {
                mid++;
            } else {
                high--;
                swap(nums, mid, high);
            }
        }
    }
};
