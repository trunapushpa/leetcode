class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int leastTillNow = prices[0];
        int maxProfit = 0;
        for (int i=1; i<prices.size(); i++) {
            if (prices[i]-leastTillNow > maxProfit) {
                maxProfit = prices[i]-leastTillNow;
            }
            leastTillNow = min(leastTillNow, prices[i]);
        }
        return maxProfit;
    }
};
