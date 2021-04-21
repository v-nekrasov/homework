#include <iostream> //������������ � ������� �������. ������ � ���������. ����������� �����. ���������� ��������� ���������.
#include<cstdlib>
#include<ctime>
#include <cmath>

using namespace std;

struct Factory; // ��������������� �������

struct Base {//������������ �����
	int x,y;
	Base(){//����������� �������� ������ ��� ����������
		x=0;y=0;
	}
	void CopyOnly(const Base &b){x=b.x; y=b.y;}
	Base(const Base &b){CopyOnly(b);}
	virtual Base &operator=(const Base &b){CopyOnly(b); return *this;}	
		 
	virtual  void pr()=0;//����� ����������� �������, ������� ��������� ���� ��������, ����� ���� �����������
	virtual ~Base(){
	}
	static Base* create_by_factory(int Type,  Factory **);
	double length(){ return sqrt(x*x + y*y);}
	Base &operator--(){this->x=-this->x; this->y=-this->y; return *this;}//--i;
};
struct Child0: public Base{//�������� �����  ���������� ������
    	//���������� �-���������� (��������)
	Child0():Base(){ 
		x=1;
	}
	Child0(const Base&a):Base(a){y=0;} //��� ���������� ������������ ����� � �������� ������ �� �������� �������� ��������� � ������������
    void pr(){//� ������ �������� ������ ������ ���� ����������� ����� ����������� ������� �������� ������
	cout<<"x="<<x<<"\n";}
	Child0 &operator=(const Base&b){x=b.x; y=0; return *this;}
};
struct Child1: public Base{//�������� ����� ��������� ������
	Child1():Base(){ 
		x=2;y=3;
	}
	Child1(const Base&a):Base(a){}//��� ���������� ������������ ����� � �������� ������ �� �������� �������� ��������� � ������������
        void pr(){
	cout<<"x="<<x<<" y="<< y<<"\n";}
};
struct Child2: public Base{//�������� �����  ���������� ������
    	//���������� x-���������� (��������)
	Child2():Base(){ 
		y=4;
	}
	Child2(const Base&a):Base(a){x=0;} //��� ���������� ������������ ����� � �������� ������ �� �������� �������� ��������� � ������������
    void pr(){//� ������ �������� ������ ������ ���� ����������� ����� ����������� ������� �������� ������
	cout<<"y="<<y<<"\n";}
	Child2 &operator=(const Base&b){cout<<"AAA"; y=b.y; x=0; return *this;}
};



struct Factory{//����������� ����� "������ �������", ��� ������� ����� ����� ����� create �� ��������� ������� (�� ������ ����� �������  ��������� ���� Base*), ����������� �� ������ ����������� �������
	virtual Base*create(int)=0;//�� ������ ����� ���� ������� ������ �� ���������, =0 ��������, ��� ������ ������� ������� ������ �������������� ��� ������� �������� ������������ ���� Base
	virtual ~Factory(){} //����� �����������, �.�. �������� �� ����������, ���������� ��������� ������ ��� ���������� ������ delete ��� ���������� �������� �������
};
struct FactoryChild0:public Factory{ //��� ���������� ������� (������� Factory), ������� ���������� ��������� �� ����� Child0
	virtual Base* create(int a){
		Child0 *t= new Child0();
		t->x=a;
		return t; //���������� ��������� �� ����������� ��� Child0
 	}
};
struct FactoryChild1:public Factory{//��� ������� ����� ����������� ��������� �� Child1
	virtual Base * create(int a){
		Child1 *t= new Child1();
		t->y=a;
		return t; //���������� ��������� �� ����������� ��� Child1
	}
};
struct FactoryChild2:public Factory{ //��� ���������� ������� (������� Factory), ������� ���������� ��������� �� ����� Child0
	virtual Base* create(int a){
		Child2 *t= new Child2();
		t->y=a;
		return t; //���������� ��������� �� ����������� ��� Child0
 	}
};

Base * Base::create_by_factory(int Type, Factory **f){ //����������� ������� ������ (����� ��� ���� ��������)
	Base *t=f[Type]->create(rand()%5); //�� ��������� ������� � ������� ������ ������ ��������� ���� �� Child0, ���� �� ����� Child1
	return t;
}

Child1 operator*(const Base&a, int s){ //���������� ��������� ��������� (������� �� ������)
		Child1 r=a; //�.�. �������� �������� ������ �� ����������, ���������� ���������� ���� �� ��������
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
//������ ������ ���������� �� ���������� ������� (�� � ��� ���), ������ ������ ��� ������������ ���������� �� Child0, ������ �� Child1
	Base **t;//��� ���� ���� -- ������ ���������� �� ������� �����
    	size_t n=7;//����� ���� �����  5 ���������� � �������
   	t=new Base*[n];//�������� ������
        for(size_t i=0;i<n;i++)
		t[i]=Base::create_by_factory(rand()%3,f);//� t ����� ��������� ������� ������������ ��������� �� Child0 � Child1
//����������� ������� ���������� ����� :: (�������� �� �����), ��� �� ��������� � �������
    for(size_t i=0;i<n;i++)
	{
		cout << "len = " << t[i]->length() << " ";
		t[i]->pr();	
	}
	Child0 r=*t[0];//������������ �������� ������ ������������  -- ��� ���� ��������, ���� �������� 
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