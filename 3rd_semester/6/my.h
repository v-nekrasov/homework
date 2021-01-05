//Задача №8
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

class Circle
{public:
	double x, y, r;
	bool f; // растёт ли окружность
	Circle(){x = 0.; y = 0.; r = 0.;  f = true;}
	Circle(double x, double y, double r, bool f){this->x = x; this->y = y; this->r = r; this->f = f;}
	int operator==(Circle &);
	friend ostream &operator<<(ostream &, const Circle &);
};

class CListNode
{   
	public:
	CListNode *next;
	Circle v;
	CListNode(){next=NULL;}
};

class CList
{
	CListNode t, *cur;
	public:
	class iterator//итератор по списку	
	{public:
		CListNode *cur;
		iterator(){cur=NULL;}
		iterator(CListNode *cur){this->cur=cur;}
		int operator!=(const iterator &b){return cur!=b.cur;}
		int operator==(const iterator &b){return cur==b.cur;}
		void operator++(){if(cur) cur=cur->next;}
		Circle& operator*(){return cur->v;}	
	};
	CList(){cur=&t;}
	~CList(){Clean();}
	CList & operator=(CList &);
	CList(CList &);
	int IsEmpty(){return t.next==NULL;}
	void Clean(){GoToBegin(); while(!IsEmpty()) DelNext();}
	int DelNext(){if(cur->next==NULL) return -1; CListNode *save=cur->next; cur->next=cur->next->next; delete save; return 0;}
	void GoToBegin(){cur=&t;}
	void GoToEnd(){for(GoToBegin(); GoToNext()==0;);}
	int GetCur(Circle&x){if(cur==&t) return -2;x=cur->v; return 0;}
	int GoToNext(){if(cur->next==NULL) return -1; cur=cur->next; return 0;}
	void AddAfter(const Circle&x){CListNode *p = new CListNode; p->v=x; p->next=cur->next; cur->next=p;}
	int Length(){int k=0; for(GoToBegin(); GoToNext()==0;) k++; return k;}		
	iterator begin(){GoToBegin(); GoToNext(); return iterator(cur);}
	iterator end(){GoToEnd(); return iterator(cur->next);}
	iterator take(int i){int k=0; for(GoToBegin(); GoToNext()==0 && k<i-1; k++); return iterator(cur);} 
};

void read_data(const char *, CList &);
void grow(CList &);
double dist(Circle, Circle);
