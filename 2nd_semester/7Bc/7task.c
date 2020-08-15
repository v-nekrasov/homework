#include"7.h"
int cmp(const void *x, const void *y)
{
    My *a=*(My**)x, *b=*(My **)y;
    return (a->group)-(b->group);
}

int is_equal(const My *one, const My *two)
{
    if((one->err == two->err)&&(one->group == two->group)&&(strcmp(one->name, two->name)==0))
       return 1;
    return 0;
}

My ** task(My ** student_1,My ** student_2, int n1, int n2, int *n)
{
    if(n1>n2)
        *n=n1;
    else
        *n=n2;
    My ** new_student=(My **)malloc(*n*sizeof(My*));
    int k = 0;
    for(int i = 0; i < n2; i++)
    {
        int fl = 0;
        for(int j = 0; j < n1; j++)
        {
            if(is_equal(student_2[i],student_1[j]))
            {
                fl = 1;
                break;
            }
        }
		for(int l = 0; l < k; l++)
			if(is_equal(student_2[i],new_student[l]))
            {
                fl = 0;
                break;
            }
        if(fl == 1)
            new_student[k++]=init(student_2[i]->group, student_2[i]->name, student_2[i]->err);
    }
    *n=k;
    return new_student;
}
