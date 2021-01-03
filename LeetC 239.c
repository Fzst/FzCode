/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
    int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    int q[numsSize];
    int left = 0, right = 0;
    for (int i = 0; i < k; ++i) {
        while (left < right && nums[i] >= nums[q[right - 1]]) {
            right--;
        }
        q[right++] = i;
    }
    *returnSize = 0;
    int* ans = malloc(sizeof(int) * (numsSize - k + 1));
    ans[(*returnSize)++] = nums[q[left]];
    for (int i = k; i < numsSize; ++i) {
        while (left < right && nums[i] >= nums[q[right - 1]]) {
            right--;
        }
        q[right++] = i;
        while (q[left] <= i - k) {
            left++;
        }
        ans[(*returnSize)++] = nums[q[left]];
    }
    return ans;
}