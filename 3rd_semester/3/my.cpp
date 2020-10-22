#include"my.h"
//печать
ostream &operator<<(ostream &cout, const CString &s){s.print(); return cout;}
ostream &operator<<(ostream &cout, const CToken &t){cout<<"'"<<t.word<<"'"; return cout;}

//старт токенизации текущей строки с заданным набором разделителей
void CTokenizer::Start() 
{
    char *p;
	int k,l,n=str.length(), pos=1;
	char* str_buf = new char[n];//буфер под строку
	memcpy(str_buf,str.ptr(),n);//взяли указатель из класса CString
	p=strtok(str_buf,sep.ptr());//выделяем первое слов
	if(p){//если в строке есть хотя бы одно слово
		CString word(p);
		l=word.length();
		k=((int)(p-str_buf)+l);
		L.Clean(); //очищаем список
		L.GoToBegin();//помещаем выделенное слово в начало списка
		L.AddAfter(CToken(word, l, pos++)); 
		L.GoToNext();//будем класть слова друг за другом, в естественном порядке
		while(k<n)//выделяем слова до конца строки
		{	
			p=strtok(NULL,sep.ptr());	
			if(p)//тут ломалась программа на Вашем тесте, т.к. не удалось выделить слово в конце строки и ptr=0
			{
				CString word(p);
				l=word.length();
				k=((int)(p-str_buf)+l);
				L.AddAfter(CToken (word, l, pos++)); 
				L.GoToNext();//будем класть слова друг за другом, в естественном порядке
			}
			else break;
		}
	}
	delete[] str_buf;
}   	

CList_tok& CList_tok::operator=(CList_tok&b)//присваивание списков
{	
	if(this!=&b)
	{
		CToken t; 
		GoToBegin(); 
		for(b.GoToBegin(); b.GoToNext()==0;)
		{
			b.GetCur(t);
			AddAfter(t);
			GoToNext();
		}  
	}	
	return *this;
}	
