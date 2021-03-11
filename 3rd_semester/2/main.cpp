#include "my.h"
int main(void)
{
	srand(time(NULL));
	CMatrix a(3), b(4), c;
	cout<<"a="<<endl<<a<<endl<<"b="<<endl<<b<<endl;
	c=a;
	cout<<"c(=a)="<<endl<<c<<endl;
	c=a+b+a;
	cout<<"c=a+b+a"<<endl<<c;
return 0;

	cout<<"c(=b)="<<endl<<c<<endl;
	cout<<"a+b="<<endl<<(a+b)<<endl;
	cout<<"++a="<<endl<<++a<<endl<<"--b="<<endl<<--b<<endl;
	cout<<"a++="<<endl<<a++<<endl<<"b--="<<endl<<b--<<endl;
	return 0;
}
