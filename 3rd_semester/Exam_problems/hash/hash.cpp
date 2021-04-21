#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class CString
{	
	char s[256]; unsigned short int n;
public:
	CString(){n=0;}
	CString(const char * s){n = strlen(s); memcpy(this->s, s, n);}
	CString(const CString &b){n=b.n; for(int i = 0; i < n; i++){s[i]=b.s[i];}}	
	CString &operator=(const CString &b){if(this != &b){n=b.n; for(int i = 0; i < n; i++){s[i]=b.s[i];}} return *this;}
	char *Get(){return s;}
	unsigned short int Length(){return n;}
	bool operator==(const CString &b){if(n != b.n) return false; for(int i = 0; i < n; i++){ if(s[i] != b.s[i]) return false;} return true;}
};

class CSet
{
	vector<CString> v;
	int n, nused;
	char *used;//битовое множество
public:
	CSet(){n=7; v.resize(n); nused = 0; used = new char[(n+7)/8]; memset(used, 0, (n+7)/8);}
	void Input(const char * file);
	~CSet(){delete[] used; used = NULL; nused = 0; n = 0;}
	bool Used(int i){return (used[i/8]) & (1<<(i%8));}
	void SetUsed(int i){(used[i/8]) |= (1<<(i%8));}
	void SetUnused(int i){(used[i/8]) &= ~(1<<(i%8));}
	int Find(CString &x){int i; for(i=H(x); Used(i); i=(i+1)%n){if(x==v[i]) return 1;} return 0;}
	int Insert(CString &x){printf("n, nused = %d, %d\n", n, nused); if(nused >= n-1) return -2; int i; for(i=H(x); Used(i); i=(i+1)%n){if(x==v[i]) return -1;} SetUsed(i); nused++; v[i]=x; return 0;}
	unsigned short int H(CString str);
	void Output();
};

void CSet::Input(const char * file)
{
	FILE *f = fopen(file, "r");
	char buf[256];
	vector<CString> tmp; 
    while(fscanf(f, "%s", buf) == 1)
	{
		tmp.push_back(CString(buf)); 	
	}
	n = 2 * tmp.size();
	v.resize(n);
	for(auto it = tmp.begin(); it != tmp.end(); ++it)
	{
		printf("I = %d\n", Insert(*it));
		for(int k = 0; k < (*it).Length(); k++)
			printf("%c", *((*it).Get()+k));
		printf("\n");			

	}
	for(auto it = v.begin(); it != v.end(); ++it)
	{
		for(int k = 0; k < (*it).Length(); k++)
			printf("%c", *((*it).Get()+k));
		printf("\n");			
	}
}

unsigned short int CSet::H(CString str)
{
	unsigned char *s = reinterpret_cast<unsigned char*>(const_cast<char*>(str.Get()));
	unsigned short int r = *s, i;
	if(str.Length() == 0) return 0;
	for(r=((r<<8)|s[1])%n, i = 0; i < str.Length(); s++, i++) 
		r=((r<<8)|s[1])%n;
	return r;
}

void CSet::Output()
{
	for(int i = 0; i < n; i++)
	{   
		char file_name[8];
		sprintf(file_name, "%d.txt", i);
		FILE *f_i = fopen(file_name, "w");
	    for(int j = 0; j < n; j++)
			if(Used(j) && H(v[j]) == i)
			{	
				for(int k = 0; k < v[j].Length(); k++)
					fprintf(f_i, "%c", *(v[j].Get()+k));
				fprintf(f_i, "\n");	
			}
	}
}

int main(void)
{
	CSet S;
	S.Input("t0.txt");
	S.Output();
	return 0;
}
