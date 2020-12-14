class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        dc = collections.defaultdict(list)
        for st in strs:
            key = "".join(sorted(st))
            dc[key].append(st)
        return list(dc.values())