bool lemonadeChange(int* bills, int billsSize){
    int f = 0,t = 0,i;
    if(bills[0] == 10 || bills[0] == 20)
        return false;
    for(i = 0;i < billsSize;i++){
        if(bills[i] == 5)
            f++;
        else if(bills[i] == 10)
            t++,f--;
        else if(t > 0 && f > 0)
            t--,f--;
        else
            f -= 3;
        if(f < 0)
            return false;
    }
    return true;
}