#include <iostream>
using namespace std;
#include "vector.h"
//-------------------------------------------------------------------
void Base::Delete(int t)
{
	int i, j = 0;
	for(i = 0; i < n; i++)              //0 1 2 0 1 2 0 1 2 0
	{	
		if(m[i] == t && test(i))
			continue;
		else
			m[j++] = m[i];
	}
	n = j;
}
bool Base::test(int t)
{
	return t < n/2;
}

bool Child::test(int t)
{
	return t >= n/2;
}
//-------------------------------------------------------------------
Child Base::operator++(void)
{
	int i, j = 0;
	for(i = 0; i < n; i++)
	{	
		if(!test(i))
		{
			m[j++] = m[i];
		}
	}
	n = j;
	return *this;
}
Child Base::operator++(int)
{
	Child r = *this;
	int i, j = 0;
	for(i = 0; i < n; i++)
	{	
		if(!test(i))
		{
			m[j++] = m[i];
		}
	}
	n = j;
	return r;
}   
 

//-------------------------------------------------------------------
Child operator+(const Base &a,const  Base &b)
{
	Child r(a.n<b.n?b.n:a.n);
	if(a.n < b.n)
	{
		for(int i = 0; i < b.n; i++)
			if(i < a.n)
				r.m[i] = a.m[i] + b.m[i];
			else
				r.m[i] = b.m[i];
	}
	else
	{
		for(int i = 0; i < a.n; i++)
			if(i < b.n)
				r.m[i] = a.m[i] + b.m[i];
			else
				r.m[i] = a.m[i];
	}
	return r;
}

ostream &operator<<(ostream &cout, const Base &v){v.print(); return cout;}

int main(void)
{
	Base V(10);
	Child v(10);
	for(int i = 0; i < 10; i++)
		{V.m[i] = i; if(i<10){v.m[i] = i;}}
	cout <<"V(base): "<<  V  <<endl <<"v(child): " <<  v << endl; 
/*	cout << "SUM" << endl;
	cout << endl << V + v + v << endl;*/
	cout << "V++ / ++v" << endl;
	cout <<"V++: "<< V++ << ", V: " << V << endl;
	cout <<"++v:" << ++v << ", v: " << v << endl;	

	v.Delete(0);
	V.Delete(5);
	cout <<"V(base): "<<  V  <<endl <<"v(child): " <<  v << endl; 

	/*Base *w = new Child(Base(10)+Child(Base(17)));
	cout << *w;
	delete w;*/
	return 0;
}