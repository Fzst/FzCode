class Solution(object):
    def containsDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        list3 =[]
        b = len(nums)
        if nums != list3 and len(nums) != 1:
             list2 = list(set(nums))
             a = len(list2)
             if b == a:
                 return False
             else:
                 return True
        else:
            return False