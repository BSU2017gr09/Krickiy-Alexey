//Индивидуальное задание №2. ДВУМЕРНЫЕ МАССИВЫ. УКАЗАТЕЛИ. ДИНАМИКА.
//76. Симметричные матрицы А(N,N) и В(N,N), заданные нижними треугольниками в виде одномерных массивов относительно главной диагонали, умножить друг на друга. В памяти матрицы не получать.

#include <iostream>
#include <clocale>
#include <iomanip>
#include <ctime>
const char* TaskInformation = "№76. Симметричные матрицы А(N,N) и В(N,N), заданные нижними треугольниками в виде одномерных массивов относительно главной диагонали, умножить друг на друга. В памяти матрицы не получать.";
typedef int MAIN_TYPE;
typedef unsigned int SIZE_TYPE;
typedef SIZE_TYPE fff(MAIN_TYPE**,MAIN_TYPE**,SIZE_TYPE);
typedef fff *pfff;
const SIZE_TYPE NUM_OF_FUNCTIONS = 5, SETW_CELL_SIZE=4;
const MAIN_TYPE MIN_VALUE=-5, MAX_VALUE=5;
using namespace std;
MAIN_TYPE** giveMemory(const SIZE_TYPE N) {
	MAIN_TYPE** A;
	try {
		A = new MAIN_TYPE*[N];
	}
	catch(...) {
		cout<<"Error.\n";
		exit(0);
	}
	for (SIZE_TYPE i=0; i<N; i++) {
		try {
			A[i]=new MAIN_TYPE[i+1];
		}
		catch(...) {
			cout<<"Error.\n";
			exit(0);
		}
	}
	return A;
} 
void freeMemory(MAIN_TYPE* *&A, const SIZE_TYPE N) {
	for (SIZE_TYPE i=0; i<N; i++) {
		delete[] A[i]; 
	}
	delete[] A;
}
void printMatrix(MAIN_TYPE* *matrix,const SIZE_TYPE N) {
	SIZE_TYPE i=0,j=0;
	for (i=0; i<N; i++) {
		for (j=0; j<i+1; j++) {
			cout<<setw(SETW_CELL_SIZE)<<matrix[i][j]<<' ';
		}
		for (j=i+1; j<N; j++) {
			cout<<setw(SETW_CELL_SIZE)<<matrix[j][i]<<' ';
		}
		cout<<'\n';
	}
}
SIZE_TYPE taskInfo(MAIN_TYPE* *A, MAIN_TYPE* *B, SIZE_TYPE N) {
	cout<<"Текст условия задачи:\n"<<TaskInformation<<'\n';
	return 0;
}
SIZE_TYPE inputMatrixes(MAIN_TYPE* *A, MAIN_TYPE* *B, SIZE_TYPE N) {
	SIZE_TYPE i=0,j=0;
	cout<<"Введите "<<(N+1)*N/2<<" элементов нижнего треугольника симметричной матрицы А("<<N<<","<<N<<"):\n";
	for (i=0; i<N; i++) {
		for (j=0; j<i+1; j++) {
			cin>>A[i][j];
		}	
	}
	cout<<"Игото матрица A:\n";
	printMatrix(A,N);
	cout<<"Введите "<<(N+1)*N/2<<" элементов нижнего треугольника симметричной матрицы B("<<N<<","<<N<<"):\n";
	for (i=0; i<N; i++) {
		for (j=0; j<i+1; j++) {
			cin>>B[i][j];
		}	
	}
	cout<<"Игото матрица B:\n";
	printMatrix(B,N);
	return 0;
}
SIZE_TYPE initMatrixes(MAIN_TYPE* *A, MAIN_TYPE* *B, SIZE_TYPE N) {//для целого MAIN_TYPE
	SIZE_TYPE i=0,j=0;
	MAIN_TYPE mod = (MAX_VALUE - MIN_VALUE+1);
	for (i=0; i<N; i++) {
		for (j=0; j<i+1; j++) {
			A[i][j]=MAIN_TYPE(rand()%mod + MIN_VALUE);
		}	
	}
	cout<<"Сгенерированная матрица А:\n";
	printMatrix(A,N);
	for (i=0; i<N; i++) {
		for (j=0; j<i+1; j++) {
			B[i][j]=MAIN_TYPE(rand()%mod + MIN_VALUE);
		}	
	}
	cout<<"Сгенерированная матрица B:\n";
	printMatrix(B,N);
	return 0;
}
SIZE_TYPE multiplyMatrixes(MAIN_TYPE* *A, MAIN_TYPE* *B, SIZE_TYPE N) {
	SIZE_TYPE i=0,j=0,k=0;
	MAIN_TYPE currentElement=0;
	printMatrix(A,N);
	cout<<"\n	*\n\n";
	printMatrix(B,N);
	cout<<"\n	||\n\n";
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			currentElement=0;
			if (i<j) {
				for (k=0; k<i+1; k++) {
					currentElement+=A[i][k]*B[j][k];
				}
				for (k=i+1; k<j+1; k++) {
					currentElement+=A[k][i]*B[j][k];
				}
				for (k=j+1; k<N; k++) {
					currentElement+=A[k][i]*B[k][j];
				}
			} else {
				for (k=0; k<j+1; k++) {
					currentElement+=A[i][k]*B[j][k];
				}
				for (k=j+1; k<i+1; k++) {
					currentElement+=A[i][k]*B[k][j];
				}
				for (k=i+1; k<N; k++) {
					currentElement+=A[k][i]*B[k][j];
				}
			}
			cout<<setw(SETW_CELL_SIZE)<<currentElement<<' ';
		}	
		cout<<'\n';
	}
	return 0;
}
SIZE_TYPE exit(MAIN_TYPE* *A, MAIN_TYPE* *B, SIZE_TYPE N) {
	exit(0);
	return 0;
}
void forEach(MAIN_TYPE* *A, MAIN_TYPE* *B, SIZE_TYPE N, pfff pf) {
	SIZE_TYPE statusError = 0;
	statusError = pf(A,B,N);
	if (statusError) {
		cout << "Не выполнено.\n";
	} else {
		cout << "Выполнено.\n";
	}
}
void menu(MAIN_TYPE* *A, MAIN_TYPE* *B, SIZE_TYPE N) {
	MAIN_TYPE userNum = 1;
	fff * Fmenu[NUM_OF_FUNCTIONS] = {taskInfo, inputMatrixes, initMatrixes, multiplyMatrixes, exit};
	while (1) {
		cout << "\nМеню:\n";
		cout << "1) Показать условие задачи\n";
		cout << "2) Ввести матрицы с клавиатуры\n";
		cout << "3) Проинициализировать матрицы случайными элементами\n";
		cout << "4) Перемножить матрицы\n";
		cout << "5) Завершить выполнение программы\n";
		cout << "Номер действия: ";
		cin >> userNum;
		if (userNum>=1 && userNum<=NUM_OF_FUNCTIONS) {
			forEach(A,B,N,Fmenu[userNum-1]);
		} else {
			cout << "Некорректный ввод.\n";
		}
	}
}
int main() {
	srand(size_t(time(NULL)));
	setlocale(LC_ALL, "ru");
	SIZE_TYPE matrixSize = 5;
	cout << "	ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ №2. ДВУМЕРНЫЕ МАССИВЫ. УКАЗАТЕЛИ. ДИНАМИКА.\n";
	cout<<"Определите размер матриц: ";
	cin>>matrixSize;
	MAIN_TYPE* *A = nullptr;
	MAIN_TYPE* *B = nullptr;
	A = giveMemory(matrixSize);
	B = giveMemory(matrixSize);
	menu(A,B,matrixSize);
	freeMemory(A,matrixSize);
	system("pause");
	return 0;
}