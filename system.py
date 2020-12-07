def meun():
    menu_info = '''＋－－－－－－－－－－－－－－－－－－－－－－＋
｜ １）添加学生信息                           ｜
｜ ２）显示所有学生的信息                     ｜
｜ ３）删除学生信息                           ｜
｜ ４）修改学生信息                           ｜
｜ ５）按学生成绩高－低显示学生信息           ｜
｜ ６）按学生成绩低－高显示学生信息           ｜
｜ ７）按学生年龄高－低显示学生信息           ｜
｜ ８）按学生年龄低－高显示学生信息           ｜
｜ ９）保存学生信息到文件（students.txt)      ｜
｜ １０）从文件中读取数据（students.txt)      ｜
｜ 退出：其他任意按键＜回车＞                 ｜
＋－－－－－－－－－－－－－－－－－－－－－－＋
'''
    print(menu_info)
def add_student_info():
    L = []
    while True:
        print("学生信息输入完毕后，按回车结束！")
        n = input("请输入姓名：")
        if not n:
            break
        try:
            a = int(input("请输入年龄："))
            b = int(input("请输入成绩："))
        except:
            print("输入无效，请重新输入信息！")
            continue
        info = {"name":n,"age":a,"score":b}
        L.append(info)
    print("学生信息输入完毕！")
    return L
def show_student_info(student_info):
    if not student_info:
        print("无学生信息！")
        return
    print("姓名".center(8),"年龄".center(4),"成绩".center(4))
    for info in student_info:
        print(info.get("name").center(10),str(info.get("age")).center(4),str(info.get("score")).center(6))
def main():
    student_info = []
    while True:
        meun()
        number = input("请输入选项：")
        if number == '1':
            student_info = add_student_info()
        elif number == '2':
            show_student_info(student_info)
        else:
            break
        input("回车显示菜单！")
main()

