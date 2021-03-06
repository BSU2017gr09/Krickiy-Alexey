//Массив чисел размера N проинициализировать случайными числами из промежутка от -N до N. Написать функцию циклического сдвига элементов массива вправо на k элементов.
//(Размер массива N запрашивать у пользователя; выделение и контроль динамической памяти прямо в main; в зависимости от задания создать одну или несколько функций для обработки массивов, которые передавать туда через указатели; •	организация циклов с использованием указателей, а не с помощью A[i])
#include <iostream>
#include <ctime>
typedef int MAIN_TYPE;
typedef unsigned int SIZE_T;
void initArray(MAIN_TYPE *pArr, const SIZE_T N, const MAIN_TYPE MIN_VALUE = 0, const MAIN_TYPE MAX_VALUE = 10) {
	std::cout<<"Initialisation array.\n";
	MAIN_TYPE *p = pArr;
	MAIN_TYPE mod;
	mod = (MAX_VALUE - MIN_VALUE+1);
	for(p=pArr; p<pArr+N; p++) *p=MAIN_TYPE(rand()%mod + MIN_VALUE); 
}
void inputSize(SIZE_T *pNumber) {
	std::cout<<"Write a size: ";
	std::cin>>*pNumber;
}
void printArray(MAIN_TYPE *pArr, const SIZE_T N, const char DELIM = '\n') {
	std::cout<<"Array:"<<DELIM;
	MAIN_TYPE *p = pArr;
	for(p=pArr; p<pArr+N; p++) std::cout<<*p<<DELIM; 
	std::cout<<'\n';
}
void reverseArray(MAIN_TYPE *pArr, SIZE_T N) {
	SIZE_T mid=N/2;
	MAIN_TYPE *p1 = pArr,*p2 = pArr+(N-1);
	MAIN_TYPE tmp = 0;
	for(p1=pArr; p1<pArr+mid; p1++,p2--) {
		tmp=*p1;
		*p1=*p2;
		*p2=tmp;
	}
}
void cyclicShiftArray(MAIN_TYPE *pArr, SIZE_T N, SIZE_T k) {//сдвиг массива вправо на k элементов
	k%=N;
	reverseArray(pArr,N-k);
	reverseArray(pArr+(N-k),k);
	reverseArray(pArr,N);
	std::cout<<"Cyclic shift array.\n";
}
int main() {
	srand(SIZE_T(time(NULL)));
	MAIN_TYPE MIN_VALUE=0, MAX_VALUE=10;
	SIZE_T N = 0;
	SIZE_T k = 6;
	inputSize(&N);
	MIN_VALUE = MAIN_TYPE(0-N);
	MAX_VALUE = MAIN_TYPE(N);
	MAIN_TYPE *pArray;
	try { 
		pArray = new MAIN_TYPE[N];
	}
	catch(...) {
		std::cout<<"Error.\n";
		exit(0);
	}
	initArray(pArray,N,MIN_VALUE,MAX_VALUE);
	printArray(pArray,N,' ');
	cyclicShiftArray(pArray,N,k);
	printArray(pArray,N,' '); 
	delete []pArray;
	system("pause");
	return 0;
}