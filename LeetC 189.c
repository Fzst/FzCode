void rotate(int* nums, int numsSize, int k){
    int n[numsSize];
    int i;
    
    for(i = 0;i < numsSize;i++)
        n[(i+k)%numsSize] = nums[i];

    for(i = 0;i < numsSize;i++)
        nums[i] = n[i];

}