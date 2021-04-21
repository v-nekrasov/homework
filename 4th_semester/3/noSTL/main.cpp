#include "my.h"
int main(void)
{
	int n, N=1000; CData0 sum0(2), l_sum0(2), r_sum0(2); CData1 sum1(2), l_sum1(2), r_sum1(2); time_t t1, t2;
	CFactory *f[2]={new CFactoryCData0(), new CFactoryCData1()};

//считывание данных из файла
	CPoly **arr = read_data("input.txt", n, f);
	if(arr == NULL)
	{		
        delete f[0];
		delete f[1];
		f[0]=f[1]=NULL;
		return 0;      
	}
//сумма всех многочленов из файла	
	
		time(&t1);
		for(int j = 0; j < N; j++)
		{
		l_sum0 = CData0(2); r_sum0 = CData0(2);
        l_sum1 = CData0(2); r_sum1 = CData0(2);
		#pragma omp parallel sections 
		{
			#pragma omp section
			{
				for(int i = 0; i < n/2; i++)
				{
					l_sum0 = l_sum0 + *(arr[i]);
					l_sum1 = l_sum1 + *(arr[i]);
				}	
			}
			#pragma omp section
            {
				for(int i = n/2; i < n; i++)
				{
					r_sum0 = r_sum0 + *(arr[i]);
					r_sum1 = r_sum1 + *(arr[i]);
				}
			}
		}
		sum0 = sum0 + l_sum0 + r_sum0;		
		sum1 = sum1 + l_sum1 + r_sum1;
		}
	time(&t2);
	cout << "parall_sum_time:  " << t2-t1 << endl;
	strcpy(sum0.FileName, "out_parall_sum.txt");
	strcpy(sum1.FileName, "out_parall_sum.txt");
	sum0.output(); //сумма напечатется в файл out_sum.txt в строку
	sum1.output(); //сумма напечатается в столбец
	
	sum0 = CData0(2);
	sum1 = CData1(2); 
	time(&t1);
	for(int j = 0; j < N; j++)
	{
	for(int i = 0; i < n; i++)
	{
		sum0 = sum0 + *arr[i];
		sum1 = sum1 + *arr[i];
	}
	}
	time(&t2);
	cout << "sum_time: " << t2-t1 << endl;
	strcpy(sum0.FileName, "out_sum.txt");
	strcpy(sum1.FileName, "out_sum.txt");
	sum0.output(); //сумма напечатется в файл out_sum.txt в строку
	sum1.output(); //сумма напечатается в столбец

	//циклический сдвиг
		CData1 r(2), r1(2), r2(2);
		
		time(&t1);
		for(int j = 0; j < N; j++)
		{	
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				r1 = *(arr[0]);    
				for(int i = 0; i < n/2-1; i++)
				{	
					*arr[i]=*arr[i+1];
				}    			
			}
			#pragma omp section
			{
			    r2 = *(arr[n/2]);    
				for(int i = n/2; i < n-1; i++)
				{	
					*arr[i]=*arr[i+1];
				}
			}	
		}
		*arr[n/2-1] = r2;
		*arr[n-1] = r1;
		}
		time(&t2);
		cout <<"parall_move_time: " << t2-t1 << endl;
		
		time(&t1);
		for(int j = 0; j < N; j++)
		{
		r = *(arr[0]);    
		for(int i = 0; i < n-1; i++)
		{	
			*arr[i]=*arr[i+1];
		}
		*arr[n-1] = r; 
        }
		time(&t2);
		cout << "move_time: " << t2-t1 << endl;
		
	
	//тест на инкремент и декремент   
		time(&t1);
	   	for(int j = 0; j < N/10; j++)
		{
		#pragma omp parallel for
			for(int i = 0; i < n; i++)
			{
				(*arr[i])++;
			}
		}
		time(&t2);
		cout << "parall_++_time: " << t2-t1 << endl;

		time(&t1);
		for(int j = 0; j < N/10; j++)
		{
	    for(int i = 0; i < n; i++)
		{
			(*arr[i])++;
		}
		}
		time(&t2);
		cout << "++_time: " << t2-t1 << endl;
		 
//освобождение памяти
	for(int i = 0; i < n; i++)
		delete arr[i]; 
	delete[] arr;        
	arr = NULL;
	delete f[0];
	delete f[1];
	f[0]=f[1]=NULL;
	return 0;
}
