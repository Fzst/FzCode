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
def del_student_info(student_info,del_name=''):
    if not del_name:
        del_name = input("请输入要删除的学生的姓名：")
    for info in student_info:
        if del_name == info.get("name"):
            return info
    return IndexError("没有找到%s！"%del_name)
def mod_student_info(student_info):
    mod_name = input("请输入要修改的学生姓名：")
    for info in student_info:
        if mod_name == info.get("name"):
            a = int(input("请输入年龄："))
            b = int(input("请输入成绩："))
            info = {"name":mod_name,"age":a,"score":b}
            return info
    return IndexError("没有找到%s!"%mod_name)



def main():
    student_info = []
    while True:
        meun()
        number = input("请输入选项：")
        if number == '1':
            student_info = add_student_info()
        elif number == '2':
            show_student_info(student_info)
        elif number == '3':
            try:
                student_info.remove(del_student_info(student_info))
            except Exception as e:
                print(e)
        elif number == '4':
            try:
                student = mod_student_info(student_info)
            except Exception as e:
                print(e)
            else:
                student_info.remove(del_student_info(student_info,del_name = student.get("name")))
                student_info.append(student)
        else:
            break
        input("回车显示菜单！")
main()
