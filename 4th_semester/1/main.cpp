#include "my.h"
int main(void)
{
	int n; CData0 sum0(2); CData1 sum1(2);
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
	for(int i = 0; i < n; i++)
	{
		sum0 = sum0 + *arr[i];
		sum1 = sum1 + *arr[i];
	}
	strcpy(sum0.FileName, "out_sum.txt");
	strcpy(sum1.FileName, "out_sum.txt");
	sum0.output(); //сумма напечатется в файл out_sum.txt в строку
	sum1.output(); //сумма напечатается в столбец

//тест на инкремент и декремент   
	cout << "INTEGRATE" << endl;
	cout << (*arr[4])++ << endl;  //выводится на экран исходный 4-ый многочлен, потом интегрируется
	cout << ++(*arr[4]) << endl;  //выводится на экран проинтегрированный четвертый многочлен (уже второй раз)
	cout << "----------" << endl;
	cout << "DIFFERENTIATE" << endl;	
	cout << (*arr[5])-- << endl;
	cout << --(*arr[5]) << endl;
	cout << "----------" << endl;

//тест на сложение и вычитание
	*arr[0] = *arr[1] + *arr[2] + CData1(15);
	*arr[3] = *arr[1] - *arr[2] - *arr[3];    

//виртуальный вывод 
	for(int i = 0; i < n; i++)
		arr[i]->output();
	
//циклический сдвиг
	CData1 r(2);
	r=*arr[0];    
	for(int i=0;i<n-1;i++)
	{	
		*arr[i]=*arr[i+1];
		strcpy(arr[i]->FileName, "out_move.txt");
	}
	strcpy(arr[n-1]->FileName, "out_move.txt");
	*arr[n-1]=r; 
//Указатели в массиве не изменили своих значений и типов, а объекты, 
//на который они указывают, циклически сдвинулись вверх на 1 позицию. 
//Теперь вывод не соответствует требуемому во входном файле, поэтому выводим результат в отдельный файл
	for(int i = 0; i < n; i++)
		arr[i]->output();
	 
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
