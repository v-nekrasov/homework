#include "my.h"
int main(void)
{
	vector<CFactory *> f = {new CFactoryCData0(), new CFactoryCData1()};
	vector<CPoly *> arr; time_t t1, t2; 
	int N = 1000;
	CData0 sum0, l_sum0, r_sum0; CData1 sum1, l_sum1, r_sum1;

//считывание данных из файла
	if(CPoly::read_data("input.txt", arr, f))	
    {
	      
	//сумма всех многочленов из файла N раз	
		
		time(&t1);
		for(int j = 0; j < N; j++)
		{
			l_sum0 = CData0(2); r_sum0 = CData0(2);
            l_sum1 = CData0(2); r_sum1 = CData0(2);
		#pragma omp parallel sections 
		{
			#pragma omp section
			{
				for(size_t i = 0; i < arr.size()/2; i++)
				{
					l_sum0 = l_sum0 + *(arr[i]);
					l_sum1 = l_sum1 + *(arr[i]);
				}	
			}
			#pragma omp section
            {
				for(size_t i = arr.size()/2; i < arr.size(); i++)
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
		cout << "parall_sum_time: " << t2-t1 << endl;
		sum0.FileName = "out_parall_sum.txt";
		sum1.FileName = "out_parall_sum.txt";
		sum0.output(); //сумма напечатется в файл out_sum.txt в строку
		sum1.output(); //сумма напечатается в столбец
		
		sum0 = CData0(2);
		sum1 = CData1(2); 
		time(&t1);
		for(int j = 0; j < N; j++)
		{
			for(size_t i = 0; i < arr.size(); i++)
			{	
				sum0 = sum0 + *(arr[i]);
				sum1 = sum1 + *(arr[i]);
			}
		}
		time(&t2);
		sum0.FileName = "out_sum.txt";
		sum1.FileName = "out_sum.txt";
		sum0.output(); //сумма напечатется в файл out_sum.txt в строку
		sum1.output(); //сумма напечатается в столбец
		cout << "sum_time: " << t2-t1 << endl;
		  
		   	

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
				for(size_t i = 0; i < arr.size()/2-1; i++)
				{	
					*arr[i]=*arr[i+1];
				}    			
			}
			#pragma omp section
			{
			    r2 = *(arr[arr.size()/2]);    
				for(size_t i = arr.size()/2; i < arr.size()-1; i++)
				{	
					*arr[i]=*arr[i+1];
				}
			}	
		}
		*arr[arr.size()/2-1] = r2;
		*arr[arr.size()-1] = r1;
		}
		time(&t2);
		cout <<"parall_move_time: " << t2-t1 << endl;
		
		time(&t1);
		for(int j = 0; j < N; j++)
		{
		r = *(arr[0]);    
		for(size_t i = 0; i < arr.size()-1; i++)
		{	
			*arr[i]=*arr[i+1];
		}
		*arr[arr.size()-1] = r; 
        }
		time(&t2);
		cout << "move_time: " << t2-t1 << endl;
		
	
	//тест на инкремент и декремент   
		time(&t1);
	   	for(int j = 0; j < N/10; j++)
		{
		#pragma omp parallel for
			for(size_t i = 0; i < arr.size(); i++)
			{
				(*arr[i])++;
			}
		}
		time(&t2);
		cout << "parall_++_time: " << t2-t1 << endl;

		time(&t1);
		for(int j = 0; j < N/10; j++)
		{
	    for(size_t i = 0; i < arr.size(); i++)
		{
			(*arr[i])++;
		}
		}
		time(&t2);
		cout << "++_time: " << t2-t1 << endl;
	
	}

	
//освобождение памяти
	
	#pragma omp parallel for
	for(size_t i = 0; i < arr.size(); i++)
	{
		delete arr[i];
		arr[i] = NULL;
	} 
	delete f[0];
	delete f[1];
	f[0]=f[1]=NULL;
	return 0;
}   
