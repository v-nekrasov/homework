#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct my{
    int group;
    char name[22];
    int err;
};
typedef struct my My;

My * init(int n, const char *s, int a){
    My *student=(My *)malloc(sizeof(My));
    student->group=n;
    student->err=a;
    strcpy(student->name,s);
    return student;
}

void print(FILE *out, My *student){
    if((student->err)==0){
        fprintf(out,"%d %s", student->group, student->name);
        fprintf(out,"%s","\n");
    }
    else{
        fprintf(stdout,"%s", "ERROR (more information in output file 2.txt)\n");
        if((student->err)==-1){
        fprintf(out,"%s", "Uncorrect group");
        fprintf(out,"%s","\n");
        }
        if((student->err)==-2){
        fprintf(out,"%s", "Uncorrect data");
        fprintf(out,"%s","\n");
        }
        if((student->err)==-3){
        fprintf(out,"%s", "No whitespace");
        fprintf(out,"%s","\n");
        }
    }
}

int pow(int a, int n)
{
    int x = 1;
    for(int i = 1; i <= n; i++)
        x *= a;
    return x;
}

My* get_student(char *buf)//получение информации об одном студенте из строки с учётом ошибок
{
    int g = 0;
    int err = 0;
    char name[22]="";
    int j = 0;
    while(buf[j] == ' ')
        j++;
    if (isdigit(buf[j]) == 0)
    {
        err = -2;
        goto le;
    }
    else
    {//считывание номера группы
        int l = 0;
        while(isdigit(buf[j+l]))
            l++;
        for(int t = 0; t < l; t++)
        {
            int x = buf[j+t] - '0';
            g = g + x * pow(10,l-1-t);
        }
        j+=l;
    }
    if(buf[j] != ' ')//проверка пробела между номером и именем
    {
        err = -3;
        goto le;
    }
    else
    {
        while(buf[j] == ' ')
            j++;
        int q = 0;
        for(j; buf[j] != ' ' && buf[j] != '\0' && q <= 22; j++, q++)
        {
            name[q]=buf[j];
        }
        name[q]='\0';
    }
    while(buf[j] == ' ')
        j++;
    if(buf[j]!='\0')
    {
        err = -2;
        goto le;
    }
    if(g < 101 || g > 626)
    {
        err = -1;
        goto le;
    }
    for(int i = 0; name[i]!='\0'; i++)// проверка на имя без посторонних символов
    {
        if(isalpha(name[i]) == 0)
        {
            err = -2;
            goto le;
        }
    }
    goto le;
    le:
     if(err==0)
         return init(g,name,err);
     else
         return init(0,"",err);
}

My ** readdata(FILE *in, int *n){
    My **a = 0;
    char buf[512];
    int k = 0;
    *n = 1;
    while(fgets(buf, 512, in) != 0)
    {
        char *ptr;
        if((ptr=strchr(buf,'\n'))!=NULL)//удаление перевода строки
            *ptr='\0';
        if(buf[0]!='\0')//если не пустая строка
        {
            k++;
            if(k == *n)
            {
                (*n) *= 2;
                a=(My**)realloc(a,sizeof(My*) * (*n));
            }
            a[k-1]=get_student(buf);
        }
    }
    *n=k;
    return a;
}
int main(){
    FILE *in = fopen("1.txt", "r");
    FILE *out = fopen("2.txt", "w");
    if(in==0)
        fprintf(stdout, "%s", "No file");
    int n;
    My **student=readdata(in,&n);
    for(int i=0;i<n;i++)
        print(out, student[i]);
    for(int i=0;i<n;i++)
        free(student[i]);
    return 0;
}

