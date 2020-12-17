class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int i;
        int pft = 0,min = prices[0];
        if(prices.size() < 2)
            return 0;
        for(i = 1;i < prices.size();i++){
            if(prices[i] < min)
                min = prices[i];
            else if(prices[i]-min-fee > 0){
                pft += prices[i]-min-fee;
                min = prices[i] - fee;
            }
        }
        return pft;
    }
};