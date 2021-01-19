#include<iostream>
using namespace std;

const double PI = 3.14;
//类
class Circle
{
public:
	//属性
	int r;
	//行为
	double cal()
	{
		return 2 * PI * r;
	}
};
class Student
{
public:
	string name;
	int id;

	void Set_Name(string name1)
	{
		name = name1;
	}
	void Set_Id(int id1)
	{
		id = id1;
	}
	void Show()
	{
		cout << "姓名为:" << name << endl;
		cout << "学号为:" << id << endl;

	}

};
int main()
{
	//对象
	Circle c;
	c.r = 10;
	cout << "圆的周长为" << c.cal() << endl;
	Student stu;
	stu.Set_Name("zhangsan");
	stu.Set_Id(1);
	stu.Show();
	return 0;
}