//java
class Solution {
    public int monotoneIncreasingDigits(int N) {
        char[] strN = Integer.toString(N).toCharArray();
        int i = 1;
        while (i < strN.length && strN[i - 1] <= strN[i]) {
            i += 1;
        }
        if (i < strN.length) {
            while (i > 0 && strN[i - 1] > strN[i]) {
                strN[i - 1] -= 1;
                i -= 1;
            }
            for (i += 1; i < strN.length; ++i) {
                strN[i] = '9';
            }
        }
        return Integer.parseInt(new String(strN));
    }
}
//c++
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string str = to_string(N);
        int i = 1;
        while(i < str.length() && str[i-1] <= str[i])
            i+=1;
        if(i < str.length()){
            while(i > 0 && str[i-1] > str[i]){
                str[i-1]-=1;
                i-=1;
            }
        
        for(i+=1;i < str.length();i++)
            str[i] = '9';
        }
        return stoi(str);

    }
};
//python3
class Solution:
    def monotoneIncreasingDigits(self, N: int) -> int:
        f = 111111111
        r = 0
        for _ in range(9):
            while f+r > N:
                f//=10
            r+=f
        return r