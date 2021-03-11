#include <iostream> //Наследование в простых классах. Пример с фабриками. Абстрактный класс. Перегрузка оператора умножения.
#include<cstdlib>
#include<ctime>
#include <cmath>

using namespace std;

struct Factory; // предопределение фабрики

struct Base {//родительский класс
	int x,y;
	Base(){//конструктор базового класса без параметров
		x=0;y=0;
	}
	void CopyOnly(const Base &b){x=b.x; y=b.y;}
	Base(const Base &b){CopyOnly(b);}
	virtual Base &operator=(const Base &b){CopyOnly(b); return *this;}	
		 
	virtual  void pr()=0;//чисто виртуальная функция, диктует интерфейс всех потомков, класс стал абстрактным
	virtual ~Base(){
	}
	static Base* create_by_factory(int Type,  Factory **);
	double length(){ return sqrt(x*x + y*y);}
	Base &operator--(){this->x=-this->x; this->y=-this->y; return *this;}//--i;
};
struct Child0: public Base{//дочерний класс  одномерный вектор
    	//забывающий у-координату (проекция)
	Child0():Base(){ 
		x=1;
	}
	Child0(const Base&a):Base(a){y=0;} //без перегрузки конструктора копии в дочернем классе не работает оператор умножения и присваивание
    void pr(){//в каждом дочернем классе должна быть перегружена чисто виртуальная функция базового класса
	cout<<"x="<<x<<"\n";}
	Child0 &operator=(const Base&b){x=b.x; y=0; return *this;}
};
struct Child1: public Base{//дочерний класс двумерный вектор
	Child1():Base(){ 
		x=2;y=3;
	}
	Child1(const Base&a):Base(a){}//без перегрузки конструктора копии в дочернем классе не работает оператор умножения и присваивание
        void pr(){
	cout<<"x="<<x<<" y="<< y<<"\n";}
};
struct Child2: public Base{//дочерний класс  одномерный вектор
    	//забывающий x-координату (проекция)
	Child2():Base(){ 
		y=4;
	}
	Child2(const Base&a):Base(a){x=0;} //без перегрузки конструктора копии в дочернем классе не работает оператор умножения и присваивание
    void pr(){//в каждом дочернем классе должна быть перегружена чисто виртуальная функция базового класса
	cout<<"y="<<y<<"\n";}
	Child2 &operator=(const Base&b){cout<<"AAA"; y=b.y; x=0; return *this;}
};



struct Factory{//абстрактный класс "вообще фабрика", его потомки будут иметь метод create по заданному образцу (из целого числа строить  указатель типа Base*), указывающий на объект конкретного потомка
	virtual Base*create(int)=0;//от класса кроме этой функции ничего не требуется, =0 означает, что каждый потомок фабрики должен переопределить эту функцию согласно родственному типу Base
	virtual ~Factory(){} //класс абстрактный, т.е. объектов не существует, деструктор необходим только для правильной работы delete при разрушении дочерней фабрики
};
struct FactoryChild0:public Factory{ //это конкретная фабрика (потомок Factory), которая производит указатели на класс Child0
	virtual Base* create(int a){
		Child0 *t= new Child0();
		t->x=a;
		return t; //возвращает указатель на родственный тип Child0
 	}
};
struct FactoryChild1:public Factory{//эта фабрика будет производить указатели на Child1
	virtual Base * create(int a){
		Child1 *t= new Child1();
		t->y=a;
		return t; //возвращает указатель на родственный тип Child1
	}
};
struct FactoryChild2:public Factory{ //это конкретная фабрика (потомок Factory), которая производит указатели на класс Child0
	virtual Base* create(int a){
		Child2 *t= new Child2();
		t->y=a;
		return t; //возвращает указатель на родственный тип Child0
 	}
};

Base * Base::create_by_factory(int Type, Factory **f){ //статическая функция класса (общая для всех объектов)
	Base *t=f[Type]->create(rand()%5); //по заданному индексу в массиве фабрик строит указатель либо на Child0, либо на класс Child1
	return t;
}

Child1 operator*(const Base&a, int s){ //перегрузка оператора умножения (вектора на скаляр)
		Child1 r=a; //т.к. объектов базового класса не существует, приходится возвращать один из дочерних
		r.x*=s;
		r.y*=s;
		return r;
}
Child1 operator--(Base & a, int){
	Child1 tmp = a;
	a.x = -a.x;
	a.y = -a.y;
	return tmp;
}//i--;


int main(){
	Child1 a; Child0 b;
	b = a;
	b.pr();
	cout << endl;
	cout << "len = " << b.length() << " ";
	cout << endl;

	srand(time(NULL));
	Factory *f[]={new FactoryChild0(),new FactoryChild1(),new FactoryChild2()};
//строим массив указателей на конкретные фабрики (их у нас две), первая служит для производства указателей на Child0, вторая на Child1
	Base **t;//это наша цель -- массив указателей на базовый класс
    	size_t n=7;//пусть надо иметь  5 указателей в массиве
   	t=new Base*[n];//выделяем память
        for(size_t i=0;i<n;i++)
		t[i]=Base::create_by_factory(rand()%3,f);//в t будут случайным образом чередоваться указатели на Child0 и Child1
//статические функции вызываются через :: (указание на класс), они не относятся к объекту
    for(size_t i=0;i<n;i++)
	{
		cout << "len = " << t[i]->length() << " ";
		t[i]->pr();	
	}
	Child0 r=*t[0];//присваивание векторов разных размерностей  -- это либо вложение, либо проекция 
	for(size_t i=0;i<n-1;i++)
		*t[i]=*t[i+1];
	*t[n-1]=r; 

	puts("____");	
	for(size_t i=0;i<n;i++)
	{
		cout << "len = " << t[i]->length() << " ";
		t[i]->pr();	
	}

        for(size_t i=0;i<n;i++)
		*t[i]=((*t[i])--)*5;
	puts("_______");
    for(size_t i=0;i<n;i++)
	{
		cout << "len = " << t[i]->length() << " ";
		(*t[i])--;
		t[i]->pr();	
	}

	for(size_t i=0;i<n;i++)
		delete t[i];
    delete []t;
	for(size_t i=0;i<3;i++)
		delete f[i];
  	return 0;
}