#include"7.h"
int main(){
    FILE *in1 = fopen("1_1.txt", "r");
    FILE *in2 = fopen("1_2.txt", "r");
    FILE *out = fopen("2.txt", "w");
    if(in1==0 || in2==0)
        fprintf(stdout, "%s", "No file");
    int n1, n2, n;
    My **student_1=readdata(in1,&n1);
    My **student_2=readdata(in2,&n2);
    My **new_student=task(student_1,student_2, n1, n2, &n);
    qsort(new_student, n, sizeof(My*), cmp);
    for(int i=0;i<n;i++)
        print(out, new_student[i]);
    my_free(student_1, n1);
    my_free(student_2, n2);
    my_free(new_student, n);
    return 0;
}
