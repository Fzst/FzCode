class Solution:
    def summaryRanges(self, nums: List[int]) -> List[str]:
        n = 0
        re = []
        while n < len(nums):
            if n+1 < len(nums) and nums[n]+1 == nums[n+1]:
                m = n#左端点
                while n+1 < len(nums) and nums[n]+1 == nums[n+1]:
                    n += 1#右端点
                re.append("{}->{}".format(nums[m],nums[n]))
            else:
                re.append(str(nums[n]))
            n += 1
        return re