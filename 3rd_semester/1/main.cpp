#include "my.h"
int main()
{
	srand(time(NULL));
	CMatrix a, b;
	cout<<"Size="<<a.size()<<endl;
	cout<<"a="<<endl<<a<<endl<<"b="<<endl<<b<<endl;
	cout<<"a+b="<<endl<<(a+b)<<endl;
	return 0;
}