class Solution:
    def prefixesDivBy5(self, A: List[int]) -> List[bool]:
        a = ""
        res = []
        for i in A:
            a += str(i)
            res.append(not int(a, 2)%5)
        return res

