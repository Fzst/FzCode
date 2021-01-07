缩写词是由一个短语中每个单词的第一个字母组成，均为大写。例如，CPU是短语“central processing unit”的缩写
def acronym(phrase):
    list1 = list(phrase.split())
    list2 = []
    for i in list1:
        list2.append(i[0])
    str2 ="".join(list2)
    return str2.upper()
phrase = input()
print(acronym(phrase))