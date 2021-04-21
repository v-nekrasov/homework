#include <iostream> //Наследование. Альтернатива  фабрикам. Абстрактный класс. Необходимый минимум по перегрузкам присваивания и конструктора копирования.
#include<cstdlib> //CopyOnly + список необходимых перегрузок
#include<ctime>
#include<cmath>
using namespace std;
struct Factory; 

struct Graph {//родительский класс
	int x; Graph *left, *right;
	Graph(int a){//конструктор базового класса без параметров
		x=a;
	}
	void CopyOnly(const Graph &a){//нужен для сложного класса
		x=a.x;
		y=a.y;
	}
	Graph(const Graph &a){//нужен для сложного класса
		CopyOnly(a);
	}
	Graph(Graph &&a){//нужен для сложного класса
		CopyOnly(a); //конечно, написан должен быть иначе
	}
       	Graph& operator=(const Graph &a){//нужен для сложного класса
		CopyOnly(a);
		return *this;
	}
  	Graph& operator=(Graph &&a){//нужен для сложного класса
		CopyOnly(a);
		return *this;
	}
	virtual  void pr()=0;//чисто виртуальная функция, диктует интерфейс всех потомков, класс стал абстрактным
	virtual ~Graph(){
	}
//способ решения задачи без фабрик, не поддерживающий принцип ООП (здесь родитель знает о своих потомках)
	static Graph* create_non_factory(int Type);//можно произвести объекты здесь, но будет нарушен принцип ООП
//способ решения задачи без фабрик, поддерживающий принципы ООП (проигрывает в сравнении с фабриками по диапазону возможностей)
	static Graph* create_by_foo(int Type,  Graph *  (*[])() );
//массив указателей на функции без параметров,  возвращающих указатели на Graph (т.е. функции типа Graph *fun(void)
};
struct List: public Graph{//дочерний класс  одномерный вектор
    	//забывающий у-координату (проекция)
	List():Graph(){ 
		x=1;
	}
	List(const Graph&a):Graph(a){y=0;} //без перегрузки конструктора копии в дочернем классе не работает оператор умножения 
        void pr(){//в каждом дочернем классе должна быть перегружена чисто виртуальная функция базового класса
	cout<<"x="<<x<<"\n";}
};
struct Tree: public Graph{//дочерний класс двумерный вектор
	Tree():Graph(){ 
		x=2;y=3;
	}
	Tree(const Graph&a):Graph(a){}//без перегрузки конструктора копии в дочернем классе не работает оператор умножения 
        void pr(){
	cout<<"x="<<x<<" y="<< y<<"\n";}
};

Tree operator*(const Graph&a, int s){ //перегрузка оператора умножения (вектора на скаляр)
		Tree r(a); //т.к. объект базового класса не существует, приходится возвращать один из дочерних
		r.x*=s;
		r.y*=s;
		return r;
}
Graph* Graph::create_non_factory(int Type) {
	if(Type==0)
		return new List;
	else
		return new Tree;
}

Graph* Graph::create_by_foo(int Type,  Graph * (*foo[])() ){
		return foo[Type]();
}
Graph * create0(){ //в аргументы ф-ции можно передать целое число, но оно будет одинаковым для всех  генерируем объектов(с использованием фабрик эту возможность можно расширить)
	return new List;
	}
Graph * create1(){
	return new Tree(a);
       }
int main(){
//что должно работать:
	List x,x1(x);//тест на конструктор копии в List
	x1=x*4*6; //тест на произведение и присваивание в List
	x.pr();x1.pr();
	Tree y,y1(y),y2(x);//тест на конструктор копии в Tree и перекрестный конструктор копии
	y1=y*2; //тест на произведение и присваивание в Tree
	x=y2=x*(-3)*2;//тест на  перекрестное присваивание 
	y.pr();y1.pr(); y2.pr();
	Graph *z=new List(x),*z1=new Tree(y);//тест на конструктор копии через указатель
	*z=y*5;*z1=y*3*55; //тест на произведение и присваивание через указатель
	z->pr();z1->pr();
	delete z1; delete z;
	srand(time(NULL));
        Graph * (*foo[])()={create0,create1};//производит объекты через указатели на функции
	Graph **t;
    	size_t n=5;//пусть надо иметь  5 указателей в массиве
   	t=new Graph*[n];//выделяем память

        for(size_t i=0;i<n;i++)
	//	t[i]=Graph::create_non_factory(rand()%3);
                t[i]=Graph::create_by_foo(rand()%2,foo);
        for(size_t i=0;i<n;i++)
		t[i]->pr();
	List r(*t[0]);//присваивание векторов разных размерностей  -- это либо вложение, либо проекция 
	for(size_t i=0;i<n-1;i++)
		*t[i]=*t[i+1];
	*t[n-1]=r; 
	puts("____");	
	for(size_t i=0;i<n;i++)
		t[i]->pr();
        for(size_t i=0;i<n;i++)
		*t[i]=*t[i]*5;
	puts("____");	
        for(size_t i=0;i<n;i++)
		t[i]->pr();
	for(size_t i=0;i<n;i++)
		delete t[i];
      	delete []t;
  	return 0;
}