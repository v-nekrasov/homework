//Задача к экзамену 1
#include<vector>
#include<list>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

vector< list<int> > create (FILE *in, int k)
{
	vector< list<int> > a(k); int n;
	while(fscanf(in, "%d", &n)==1)
		a[n%k].push_back(n);
	return a;		
}
int main()
{
	FILE *in=fopen("3.txt", "r"); int k;
	cout<<"k=";
	cin>>k;
	vector< list<int> > a=create(in, k);
	fclose(in);
	cout<<"result"<<endl;
	vector< list<int> >::iterator t1;
	list<int>::iterator t2;
	for(t1=a.begin();t1!=a.end(); t1++)
	{
		for(t2=(*t1).begin(); t2!=(*t1).end(); t2++)
			printf("%d ", *t2);
		printf("\n");
	}		

 
	return 0;
}