/*1、首先将原字符串中的' '与'-'去掉，可定义一个指针变量，类型为char型，从原字符串开头遍历，如果当前字符不是' '或'-'，更新原字符串，直到最后一个字符。
2、将原字符串进行处理过后，先对现字符串的个数进行统计，如果当前字符串的个数小于4，则直接返回此字符串，否则，即分为以下3种情况：
1：当字符串个数大于4时，将原字符串顺序相连的3个字符直接''赋值''给所求字符串，然后在末尾加上字符'-'。
2：当字串串个数等于4时，将原字符串顺序相连2个字符直接''赋值''给所求字符串，然后添加字符'-'，然后将最后两个字符''赋值''给所求字符串。
3：当字符串个数等于3或2或1时，将原字符串剩下的字符顺序''赋值''给所求字符串。
3、在所求字符串的末尾加字符'\0'，标志结束。

作者：fzst
链接：https://leetcode-cn.com/problems/reformat-phone-number/solution/cyu-yan-ti-jie-fen-lei-tao-lun-by-fzst-4pk1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/
char * reformatNumber(char * number){
    int m = 0,k;
    int k1 = 0;
    int m1 = 0;
    int n;
    int u = 0;
    char nums[120];//定义所求的字符数组
    static char res[120];
    char *p = number;
    while(*p){
        if(*p != ' ' && *p != '-')
            number[u++] = *p;
        p++;
    }
    number[u] = '\0';
    n = strlen(number);
    if(n < 4){
        strcpy(res,number);
        return res;
    }else{
        while(m1 != n-1){ //循环结束条件
            k = strlen(number)-m1;//剩余数字个数
            if(k > 4){
                for(k1 = 0;k1 < 3;k1++){
                    nums[m++] = number[m1++];
                }nums[m++] = '-';
            }else if(k == 3){
                nums[m++] = number[m1++];
                nums[m++] = number[m1++];
                nums[m] = number[m1];
            }else if(k == 2){
                nums[m++] = number[m1++];
                nums[m] = number[m1];
            }else if(k == 1){
                nums[m] = number[m1];
            }
            else if(k == 4){
                nums[m++] = number[m1++];
                nums[m++] = number[m1++];
                nums[m++] = '-';
                nums[m++] = number[m1++];
                nums[m] = number[m1];
            }
        }
    }
    nums[m+1] = '\0';//结束标志
    strcpy(res,nums);
    return res;
}
/*
作者：fzst
        链接：https://leetcode-cn.com/problems/reformat-phone-number/solution/cyu-yan-ti-jie-fen-lei-tao-lun-by-fzst-4pk1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/