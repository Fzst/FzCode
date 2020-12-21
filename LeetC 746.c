int minCostClimbingStairs(int* cost, int costSize){
    int dp[costSize+1];
    dp[0] = dp[1] = 0;//初始状态花费0体力
    for(int i = 2;i <= costSize;i++)
        dp[i] = fmin(dp[i-1] + cost[i-1],dp[i-2] + cost[i-2]);//状态转移方程
    return dp[costSize];

}