#pragma once
//Задача №5 Токенайзер текстовой строки
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
using namespace std;
//-------------------------------------------------------------------
class CString//реализация строки с лекции Владимира Михайловича --- чтобы всё сделать без констант
{
 	char *s; int n;
	public:
	CString(const char*s=NULL){if(s){n=strlen(s)+1; memcpy(this->s=new char[n+1],s,n+1); } else SetZero();}//конструктор с параметром по умолч.(может использоваться вместо констр. по умолч.) + место под ноль-терм.
	~CString(){Clean();}
	CString(const CString &b){CopyOnly(b);}
	CString(CString&&b){CopyOnly_(b);}//move-constructor
	CString &operator=(const CString &b){if(this!=&b){Clean(); CopyOnly(b);} return *this;}
	CString &operator=(CString &&b){if(this!=&b){Clean(); CopyOnly_(b);} return *this;}//move-assignment
	void Clean(){delete[] s; SetZero();}
	void SetZero(){s=NULL; n=0;}
	void CopyOnly(const CString &b){n=b.n; memcpy(s=new char[n], b, n);}
	void CopyOnly_(CString &b){n=b.n; s=b.s; b.SetZero();}
	operator const char*()const{return s;}
	void print()const{for(int i=0; i<n-1; i++) cout<<s[i];}
	int length()const{return n;}
	char *ptr(){return s;}
	char &operator[](int i){if(i<0||i>=n)throw -1; return s[i];}
	friend ostream &operator<<(ostream &cout, const CString &s);	
};
//-------------------------------------------------------------------
//Токен для хранения информации о слове
class CToken 
{	CString word;//слово длиной не более 64 символов
	int len;//длина слова
	int pos;//позиция слова в строке --- у первого слова pos = 1
	public:
	CToken(){pos=0;}
	CToken(CString word, int len, int pos){this->word=word; this->len=len; this->pos=pos;}
	friend ostream &operator<<(ostream &cout, const CToken & t); 	
};

//-------------------------------------------------------------------
//Реализация однонаправленного списка (написал на лекции Владимира Михайловича) для хранения токенов + итератор  
class CListNode_tok
{   
	public:
	CListNode_tok *next;
	CToken v;
	CListNode_tok(){next=NULL;}
};
class CList_tok
{
	CListNode_tok t, *cur;
	public:
	class iterator//итератор по списку	
	{public:
		CListNode_tok *cur;
		iterator(){cur=NULL;}
		iterator(CListNode_tok *cur){this->cur=cur;}
		int operator!=(const iterator &b){return cur!=b.cur;}
		int operator==(const iterator &b){return cur==b.cur;}
		void operator++(){if(cur) cur=cur->next;}
		CToken operator*(){return cur->v;}	
	};
	CList_tok(){cur=&t;}
	~CList_tok(){Clean();}
	CList_tok & operator=(CList_tok&b);
	int IsEmpty(){return t.next==NULL;}
	void Clean(){GoToBegin(); while(!IsEmpty()) DelNext();}
	int DelNext(){if(cur->next==NULL) return -1; CListNode_tok *save=cur->next; cur->next=cur->next->next; delete save; return 0;}
	void GoToBegin(){cur=&t;}
	void GoToEnd(){for(GoToBegin(); GoToNext()==0;);}
	int GetCur(CToken&x){if(cur==&t) return -2;x=cur->v; return 0;}
	int GoToNext(){if(cur->next==NULL) return -1; cur=cur->next; return 0;}
	void AddAfter(const CToken&x){CListNode_tok *p = new CListNode_tok; p->v=x; p->next=cur->next; cur->next=p;}
	int Length(){int k=0; for(GoToBegin(); GoToNext()==0;) k++; return k;}		
	iterator begin(){GoToBegin(); GoToNext(); return iterator(cur);}
	iterator end(){GoToEnd(); return iterator(cur->next);}
	iterator take(int i){int k=0; for(GoToBegin(); GoToNext()==0 && k<i-1; k++); return iterator(cur);} 
};
//-------------------------------------------------------------------
//Реализация токенайзера
class CTokenizer
{   
	CString str;//строка 
	CString sep;//разделители
	CList_tok L; //список для хранения токенов
	public:
	class iterator//пришлось сделать итератор из итератора для списка	
	{public:
		CList_tok::iterator it;
		iterator(){}
		iterator(CList_tok::iterator it){this->it=it;}
		int operator!=(const iterator &b){return it!=b.it;}
		int operator==(const iterator &b){return it==b.it;}
		void operator++(){++it;}
		CToken operator*(){return *it;}		
	};
	CTokenizer(){}//конструкторы работают в классах CString и CList_tok
	CTokenizer(CString str, CString sep){this->str=str; this->sep=sep;}//инициализация токенизируемой строки и разделителей             
	CTokenizer(CTokenizer &b){this->str=b.str; this->sep=b.sep; this->L=b.L;}//конструктор копирования
	CTokenizer &operator=(CTokenizer &b){if(this!=&b){this->str=b.str; this->sep=b.sep; this->L=b.L;} return *this;}
	//--далее методы класса
	void Start();//старт токенизации --- разбить строку на токены(см. my.cpp)
	int Count(){return L.Length();}//общее количество найденных токенов
	CString Sep(){return sep;}
	void Change_sep(CString new_sep){sep=new_sep;}//изменить набор разделителей
	//--итераторы
	iterator first(){return iterator(L.begin());}
	iterator last(){return iterator(L.end());}
	iterator get(int i){if(i<=L.Length()){return iterator(L.take(i));} else {throw -1; return iterator(L.end());}}//i-ый токен
};                         
