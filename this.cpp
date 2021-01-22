#include<iostream>
using namespace std;
class Person
{
public:
	Person(int age)
	{
		this->age = age;
	}
	Person& Add(Person& p)
	{
		this->age += p.age;
		return *this;
	}
	void init() const
	{
		this->size = 100;
	}
	int age;
	mutable int size;
};
void te()
{
	//const Person p;
	Person p1(18);
	Person p2(18);
	p2.Add(p1).Add(p1);
	cout << "kkk=" << p2.age << endl;
}
int main()
{
	te();
	return 0;
}