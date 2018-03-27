//МПиИ на 28.03.2018, пример класса комплексных чисел. Перегрузка операторов.
#include <iostream>
#include <clocale>
typedef float MAIN_TYPE;
using namespace std;
class Complex
{//работа с действительным числом только как с правым операндом
	public:
		MAIN_TYPE a;
		MAIN_TYPE b;
		Complex():
			a(0),
			b(0) 
		{ 
			//cout<<"Работает конструктор"<<endl; 
		};
		Complex(const Complex &other) {
			//cout<<"Работает copy конструктор"<<endl;
			a = other.a;
			b = other.b;
		};
		Complex(MAIN_TYPE a):
			a(a)
		{
			//cout<<"Работает конструктор c параметром"<<endl;
		};
		Complex(MAIN_TYPE a, MAIN_TYPE b):
			a(a),
			b(b)
		{
			//cout<<"Работает конструктор c параметрами"<<endl;
		};
		~Complex() {
			//cout<<"Работает деструктор"<<endl;
		}
		Complex& operator=(const Complex &other) {
			//cout<<"Работает оператор присваивания"<<endl;
			a = other.a;
			b = other.b;
			return (*this);
		};
		MAIN_TYPE abs() {
			return sqrt(a*a+b*b);
		}
		Complex inverse() {
			if (a || b) {
				MAIN_TYPE denominator = a*a+b*b;
				return Complex(a/denominator,-b/denominator);
			} else {
				cout<<"Ошибка: не существует обратного для 0."<<endl;
				return Complex(0,0);
			}
		}
		Complex paired() {
			return Complex(a,-b);
		}
		Complex operator+(const Complex &other) {
			//cout<<"Работает оператор +"<<endl;
			return Complex(a+other.a, b+other.b);
		};
		Complex operator+(const MAIN_TYPE real) {
			//cout<<"Работает оператор +"<<endl;
			return Complex(a+real, b);
		};
		Complex& operator+=(const Complex &other) {
			//cout<<"Работает оператор +="<<endl;
			a += other.a;
			b += other.b;
			return (*this);
		};
		Complex& operator+=(const MAIN_TYPE real) {
			//cout<<"Работает оператор +="<<endl;
			a += real;
			return (*this);
		};
		Complex operator-(const Complex &other) {
			//cout<<"Работает оператор -"<<endl;
			return Complex(a-other.a, b-other.b);
		};
		Complex operator-(const MAIN_TYPE real) {
			//cout<<"Работает оператор -"<<endl;
			return Complex(a-real, b);
		};
		Complex& operator-=(const Complex &other) {
			//cout<<"Работает оператор -="<<endl;
			a -= other.a;
			b -= other.b;
			return (*this);
		};
		Complex& operator-=(const MAIN_TYPE real) {
			//cout<<"Работает оператор -="<<endl;
			a -= real;
			return (*this);
		};
		Complex operator*(const Complex &other) {
			//cout<<"Работает оператор *"<<endl;
			return Complex(a*other.a-b*other.b, a*other.b+b*other.a);
		};
		Complex operator*(const MAIN_TYPE real) {
			//cout<<"Работает оператор *"<<endl;
			return Complex(a*real, b*real);
		};
		Complex& operator*=(const Complex &other) {
			//cout<<"Работает оператор *="<<endl;
			a = a*other.a-b*other.b;
			b = a*other.b+b*other.a;
			return (*this);
		};
		Complex& operator*=(const MAIN_TYPE real) {
			//cout<<"Работает оператор *="<<endl;
			a = a*real;
			b = b*real;
			return (*this);
		};
		Complex operator/(const Complex &other) {
			//cout<<"Работает оператор /"<<endl;
			if (a || b) {
				MAIN_TYPE denominator = other.a*other.a+other.b*other.b;
				return Complex((a*other.a+b*other.b)/denominator, (b*other.a-a*other.b)/denominator);
			} else {
				cout<<"Ошибка: деление на 0."<<endl;
				exit(0);
			}
		};
		Complex operator/(const MAIN_TYPE real) {
			//cout<<"Работает оператор /"<<endl;
			if (real) return Complex(a/real, b/real);
			else {
				cout<<"Ошибка: деление на 0."<<endl;
				exit(0);
			}
		};
		Complex& operator/=(const Complex &other) {
			//cout<<"Работает оператор /="<<endl;
			if (a || b) {
				MAIN_TYPE denominator = other.a*other.a+other.b*other.b;
				a = (a*other.a+b*other.b)/denominator;
				b = (b*other.a-a*other.b)/denominator;
			} else {
				cout<<"Ошибка: деление на 0."<<endl;
				exit(0);	
			}
			return (*this);
		};
		Complex& operator/=(const MAIN_TYPE real) {
			//cout<<"Работает оператор /="<<endl;
			if (real) {
				a /= real;
				b /= real;
			} else {
				cout<<"Ошибка: деление на 0."<<endl;
				exit(0);
			}
			return (*this);
		};
		
		friend ostream& operator<<(ostream &myStream, Complex &tmp) {
			if (tmp.a) cout<<tmp.a;
			if (tmp.b) {
				if (tmp.b>0 && tmp.a) cout<<'+';
				cout<<tmp.b<<'i';
			} else {
				if (!tmp.a) cout<<'0';
			}
			cout<<endl;
			return myStream;
		};
		friend istream& operator>>(istream &myStream, Complex &tmp) {
			cout<<"Введите действительную и мнимую части числа через пробел: ";
			cin>>tmp.a>>tmp.b;
			return myStream;
		};
};
int main() {
	setlocale(LC_ALL, "ru");
	Complex A(5,-2.2);
	Complex B(A.paired());
	cout<<B;
	cin>>A;
	B+=1;
	A*=B;
	B=A/5;
	cout<<B-A;
	cout<<B.inverse();
	cout<<B.abs()<<endl;
	system("pause");
	return 0;
}
