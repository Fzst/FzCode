class Solution {
public:
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        int suma = accumulate(A.begin(),A.end(),0);
        int sumb = accumulate(B.begin(),B.end(),0);
        int val = (suma - sumb)/2;
        sort(A.begin(), A.end(), less<int>());
        sort(B.begin(), B.end(), less<int>());
        vector<int>re;
        int i = 0;
        int j = 0;
        while(i < A.size() && j < B.size())
        {
            int temp = A[i] - B[j];
            if(temp == val)
            {
                re.push_back(A[i]);
                re.push_back(B[j]);
                return re;
            }
            else if(temp > val)
                j++;
            else
                i++;
        }
        return vector<int>();

    }
};