class Solution {
public:
    string removeDuplicates(string S) {
        string re;
        for(auto str : S)
        {
            if(!re.empty() && re.back() == str)
            {
                re.pop_back();
            }
            else
            re.push_back(str);
        }
        return re;
    }
};

