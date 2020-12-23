int firstUniqChar(char * s){
    int n = strlen(s),i;
    int hash[26] = {0};
    for(i = 0;i < n;i++)
        hash[s[i]-'a']++;
    for(i = 0;i < n;i++){
        if(hash[s[i]-'a'] == 1)
            return i;
    }
    return -1;
}