class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int to = 0;
        int left = 0;
        for(int i = 0;i < nums.size();i++)
            to += nums[i];
        for(int i = 0;i < nums.size();i++)
        {
            if(2*left + nums[i] == to)
                return i;
            left += nums[i];
        }
        return -1;
    }
};