int cmp(const void* _a , const void* _b)
{
    char* a = (char*)_a;
    char* b = (char*)_b;
    return *a - *b;
}
char findTheDifference(char * s, char * t){
    qsort(s,strlen(s),sizeof(s[0]),cmp);
    qsort(t,strlen(t),sizeof(t[0]),cmp);
    int i;
    if(strlen(s) == 0){
        return t[0];
    }else{
    for(i = 0;i < strlen(s);i++){
        if(t[i] != s[i]){
        	return t[i];
        }              
    }
    }
    return t[i];
}