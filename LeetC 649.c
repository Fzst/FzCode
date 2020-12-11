char * predictPartyVictory(char * senate){
    int r = 0,d = 0,i;
    int lr = 0,ld = 0;
    static char ra[8];
    strcpy(ra,"Radiant");
    static char di[5];
    strcpy(di,"Dire");
    while(1){
        r = 0;
        d = 0;
        for(i = 0;i < strlen(senate);i++){
                if(senate[i] == 'R'){
                    if(lr >= ld)
                        lr++;
                    else{
                        ld--;
                        senate[i] = '0';
                    }
                    r++;
                }
                else if(senate[i] == 'D'){
                    if(ld >= lr)
                        ld++;
                    else{
                        lr--;
                        senate[i] = '0';
                    }
                    d++;
                }
        }
        if(r == 0 || d == 0)
            break;
    }
    if(r > d)
        return ra;
        else
        return di;
}


