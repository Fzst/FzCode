int cmp_int(const void* _a , const void* _b)
{
    int a = *(int*)_a;
    int b = *(int*)_b;
    return a - b;
}
bool containsDuplicate(int* nums, int numsSize){
    qsort(nums,numsSize,sizeof(int),cmp_int);
    for(int i = 0;i < numsSize-1;i++){
        if(nums[i] == nums[i+1])
            return true;
    }
    return false;
}