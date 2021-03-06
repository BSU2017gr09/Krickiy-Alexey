//Разработать программу для работы с одним или несколькими одномерными массивами в heap, предусмотрев в ней:
 // - Размер массива N запрашивать у пользователя;
 // - выделение и контроль динамической памяти в отдельной функции, а не в main;
 // - организация циклов с использованием указателей, а не с помощью A[i];
 // - функции для инициализации, для ввода, для вывода массивов в heap;
 // - удаление динамической памяти после её использования желательно, но пока не обязательно в отдельной функции;
 // - одну или несколько функций для обработки массивов (для сортировки новый массив не создавать);
//4. Элементы целочисленного массива А(N), значения которых оказались простыми числами, расположить в порядке возрастания, не нарушая порядка следования других элементов.

#include <cstdlib>
#include <iostream>
#include <ctime>
typedef int MAIN_TYPE;
typedef unsigned int SIZE_T;
typedef MAIN_TYPE* P_MAIN_TYPE;
const MAIN_TYPE MIN_VALUE=3, MAX_VALUE=10;
void newArray(MAIN_TYPE *&pArr, const SIZE_T N) {
	try { 
		pArr = new MAIN_TYPE[N];
	}
	catch(...) {
		std::cout<<"Error.\n";
		exit(0);
	}
}
void newArray(P_MAIN_TYPE *&pArr, const SIZE_T N) {
	try { 
		pArr = new P_MAIN_TYPE[N];
	}
	catch(...) {
		std::cout<<"Error.\n";
		exit(0);
	}
}
void deleteArray(MAIN_TYPE *&pArr) {
	delete []pArr;
}
void deleteArray(P_MAIN_TYPE *&pArr) {
	delete []pArr;
}
void initArray(MAIN_TYPE *pArr, const SIZE_T N, const MAIN_TYPE MIN_VALUE = 0, const MAIN_TYPE MAX_VALUE = 10) {
	MAIN_TYPE *p = pArr;
	MAIN_TYPE mod;
	mod = (MAX_VALUE - MIN_VALUE+1);
	for(p=pArr; p<pArr+N; p++) *p=MAIN_TYPE(rand()%mod + MIN_VALUE); 
}
void inputArray(MAIN_TYPE *pArr, const SIZE_T N) {
	MAIN_TYPE *p = pArr;
	for(p=pArr; p<pArr+N; p++) std::cin>>(*p); 
}
void printArray(MAIN_TYPE *pArr, const SIZE_T N, const char DELIM = '\n') {
	MAIN_TYPE *p = pArr;
	for(p=pArr; p<pArr+N; p++) std::cout<<*p<<DELIM;
	std::cout<<'\n';
}
void sortArray(MAIN_TYPE *pLeftBoarder, MAIN_TYPE *pRightBoarder) {
	//Сортировка Хоара
	MAIN_TYPE *i = pLeftBoarder, *j = pRightBoarder;
	MAIN_TYPE x = *(pLeftBoarder+((pRightBoarder-pLeftBoarder)/2));
	do {
		while(*i<x) i++;
		while(*j>x) j--;
		if (i<=j) {
			if (i<j) {
				std::swap(*i,*j);
			}
			i++;
			j--;
		}
	} while (i<=j);
	if (i<pRightBoarder) sortArray(i,pRightBoarder);
	if (j>pLeftBoarder) sortArray(pLeftBoarder,j);
}
void sortArray(P_MAIN_TYPE *pLeftBoarder, P_MAIN_TYPE *pRightBoarder) {
	//Сортировка Хоара для массива указателей
	P_MAIN_TYPE *i = pLeftBoarder, *j = pRightBoarder;
	MAIN_TYPE x = **(pLeftBoarder+((pRightBoarder-pLeftBoarder)/2));
	do {
		while(**i<x) i++;
		while(**j>x) j--;
		if (i<=j) {
			if (i<j) {
				std::swap(**i,**j);
			}
			i++;
			j--;
		}
	} while (i<=j);
	if (i<pRightBoarder) sortArray(i,pRightBoarder);
	if (j>pLeftBoarder) sortArray(pLeftBoarder,j);
}
bool isPrime(MAIN_TYPE number) {
	if (number<2) return false;
	if (number == 2) return true;
	if (!(number%2)) return false;
	double maxDivider = sqrt(number);
	for (SIZE_T i=3; i<=maxDivider; i+=2) {
		if (!(number%i)) return false;
	}
	return true;
}
void sortOnlyPrimeElements(MAIN_TYPE *pArr, SIZE_T N) {
	MAIN_TYPE *p=pArr;
	SIZE_T listLen = 0;
	P_MAIN_TYPE *pListOfPrimeElements;
	newArray(pListOfPrimeElements,N);
	for (p=pArr; p<pArr+N; p++) {
		if (isPrime(*p)) {
			*(pListOfPrimeElements+listLen)=p;
			listLen++;
			
		}
	}
	sortArray(pListOfPrimeElements,pListOfPrimeElements+listLen-1);
	deleteArray(pListOfPrimeElements);
}
int main() {
	srand(SIZE_T(time(NULL)));
	SIZE_T N=1;
	MAIN_TYPE *A = 0;
	while(1) {
		std::cout<<"Write a size of array: ";
		std::cin>>N;
		if (!N) std::cout<<"Try again. ";
		else break; 
	}
	newArray(A,N);
	initArray(A,N,MIN_VALUE,MAX_VALUE);
	std::cout<<"Array: ";
	printArray(A,N,' ');
	std::cout<<"Result: ";
	sortOnlyPrimeElements(A,N);
	printArray(A,N,' ');
	deleteArray(A);
	system("pause");
	return 0;
}