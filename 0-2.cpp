//В массиве размера N, заполненного случ.числами от 0 до 10, определить максимальную длину последовательности равных элементов.
//(Размер массива N запрашивать у пользователя; выделение и контроль динамической памяти прямо в main; в зависимости от задания создать одну или несколько функций для обработки массивов, которые передавать туда через указатели; •	организация циклов с использованием указателей, а не с помощью A[i])
#include <iostream>
#include <ctime>
typedef int MAIN_TYPE;
typedef unsigned int SIZE_T;
const MAIN_TYPE MIN_VALUE=0, MAX_VALUE=10;
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
SIZE_T maxLenSequenceSameElem(MAIN_TYPE *pArr, const SIZE_T N) {
	SIZE_T maxLenSequenceSameElements = 1;
	SIZE_T lenSequenceSameElements = 1;
	MAIN_TYPE *p = pArr;
	MAIN_TYPE *prevElement = pArr;
	if (N) {
		for(p=pArr+1; p<pArr+N; p++) {
			if (*p==*prevElement) {
				lenSequenceSameElements++;
			} else {
				if (lenSequenceSameElements>maxLenSequenceSameElements) maxLenSequenceSameElements=	lenSequenceSameElements;
				lenSequenceSameElements = 1;
				prevElement=p;
			}
		}
		if (lenSequenceSameElements>maxLenSequenceSameElements) maxLenSequenceSameElements=	lenSequenceSameElements;
	} else {
		maxLenSequenceSameElements=0;
	}
	std::cout<<"The maximum length of sequence of equal elements in the array: "<<maxLenSequenceSameElements<<'\n';
	return maxLenSequenceSameElements;
}
int main() {
	srand(SIZE_T(time(NULL)));
	SIZE_T N = 0;
	SIZE_T answer = 0;
	inputSize(&N);
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
	answer=maxLenSequenceSameElem(pArray,N);
	delete []pArray;
	system("pause");
	return 0;
}