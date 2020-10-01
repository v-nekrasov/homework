//Задача к экзамену 2
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
vector< vector<int> > create(FILE *in);
vector< vector<int> > create(FILE *in)
{
	vector< vector<int> > a;
	char buf[256], *s;
	while(fgets(buf, 256, in)!=0)
	{
		vector<int> b;
		int pos, x; s=buf; 
		while(sscanf(s,"%d%n",&x,&pos)==1)
		{
			b.push_back(x);
			s+=pos;
		}
		a.push_back(b);
	}	
	return a;		
}
int main()
{
	FILE *in=fopen("0.txt", "r"); 
	vector< vector<int> > a=create(in);
	fclose(in);
	cout<<"result"<<endl;
	vector< vector<int> >::iterator t1;
	vector<int>::iterator t2;
	for(t1=a.begin();t1!=a.end(); t1++)
	{
		for(t2=(*t1).begin(); t2!=(*t1).end(); t2++)
			printf("%d ", *t2);
		printf("\n");
	}		
	return 0;
}