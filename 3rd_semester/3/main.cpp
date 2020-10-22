#include "my.h"
int main(void)//тесты
{   
try{
	FILE *in=fopen("sep.txt", "r");
	char sep_buf[64];
	fgets(sep_buf, 64, in);
	fclose(in);
	CString sep(sep_buf);
	CString STR(" I _ love informatics__   ___and_C++ language___");
	cout<<"String=("<<STR<<")"<<endl;	
	cout<<"---"<<endl;
	//--  
	CTokenizer tok(STR, sep);//создали токенайзер
	tok.Start();//запустили токенизацию
	cout<<"There are "<<tok.Count()<<" tokens with sep=("<<tok.Sep()<<") in this string:"<<endl;//Получилось всего _ слов
	CTokenizer:: iterator it; //итератор по списку, который лежит в токенайзере
	for(it=tok.first(); it!=tok.last(); ++it) //распечатали полученные токены
		cout<<*it<<" ";
	cout<<endl;
	cout<<"---"<<endl;
	//--
	sep[0]='_';
	tok.Change_sep(sep);//поменяли разделители
	tok.Start();//запустили токенизацию
	cout<<"There are "<<tok.Count()<<" tokens with sep=("<<tok.Sep()<<") in this string:"<<endl;//Получилось всего _ слов
	for(it=tok.first(); it!=tok.last(); ++it) //распечатали полученные токены
		cout<<*it<<" ";
	cout<<endl;
	cout<<"---"<<endl;
	//--
	cout<<"3-rd token: "<<*(tok.get(3))<<endl;//Можем создать итератор tok.get(i) для произвольной позиции
	cout<<"---"<<endl;					//Достали третий токен (нумерация с 1) из итератора   
	//--
	CTokenizer tok2=tok;
	cout<<"3-rd token in tok2: "<<*(tok2.get(3));	
	}catch(...){printf("error\n");}
	return 0;
}
