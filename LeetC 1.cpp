//LeetCode 1
//给定一个整数数组 nums和一个目标值 target，请你在该数组中找出和为目标值的那?两个?整数，并返回他们的数组下标。
//你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
#include<stdio.h>
#include<stdlib.h>
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i,j;
    int *re;
    for(i = 0;i < numsSize;i++){
        for(j = i+1;j < numsSize;j++){
            if(nums[i] + nums[j] == target){
            	re = (int *)malloc(sizeof(int ));
            	re[0] = i;
            	re[1] = j;
            	*returnSize = 2;
                return re;
            }
        }
    }
    *returnSize = 0;
    return NULL;

}
int main(){
    int nums[100] = {2,7,11,15};
    int *returnSize = (int *)malloc(sizeof(int ));
    int target = 9;
    returnSize = twoSum(nums,4,target,returnSize);
    for(int i = 0;i < 2;i++)
		printf("%d ",returnSize[i]); 

    return 0;
}



