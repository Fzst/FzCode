//LeetCode 1
//����һ���������� nums��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ����?����?���������������ǵ������±ꡣ
//����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ�������ͬһ��Ԫ�ز���ʹ�����顣
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



