int cmp(int *a,int *b){
    return *a-*b;
}

int findContentChildren(int* g, int gSize, int* s, int sSize){
    int count = 0,i;
    qsort(g,gSize,sizeof(int),cmp);
    qsort(s,sSize,sizeof(int),cmp);
    for(i = 0;count < gSize && i < sSize;i++){
        if(g[count] <= s[i])
            count++;
    }
    return count;
}