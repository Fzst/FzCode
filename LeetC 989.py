class Solution:
    def addToArrayForm(self, A: List[int], K: int) -> List[int]:
        n = ''
        for i in A:
            n += str(i)
        n = str(int(n) + K)
        re = []
        for i in n:
            re.append(i)
        re = list(map(int,re))
        return re