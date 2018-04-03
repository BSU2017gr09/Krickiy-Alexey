//ЗАДАНИЕ на 04.04.2018, задача 16.
//№16. 17.	В структуре хранится информация о движении самолётов: номер рейса, пункт назначения, время вылета, информация о наличии свободных мест.
//a) По запросу вывести информацию об указанном рейсе.
//b) Выдать по заявке пассажира билет, если есть свободные места на указанный рейс. Предложить другой рейс, если на указанный рейс нет билетов, или вывести сообщение о невозможности вылета в указанный пункт.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include <iomanip>
#include <ctime>
#include <cstring>
const char* TaskInformation = "№16. 17.	В структуре хранится информация о движении самолётов: номер рейса, пункт назначения, время вылета, информация о наличии свободных мест.\na)	По запросу вывести информацию об указанном рейсе.\nb)	Выдать по заявке пассажира билет, если есть свободные места на указанный рейс. Предложить другой рейс, если на указанный рейс нет билетов, или вывести сообщение о невозможности вылета в указанный пункт.";
unsigned long int numOfFlight=0;
typedef float MAIN_TYPE;
typedef unsigned int SIZE_TYPE;
const unsigned int MAX_NUM_OF_SEATS = 500;
const SIZE_TYPE N = 100;
typedef SIZE_TYPE fff(char *);
typedef fff *pfff;
const SIZE_TYPE NUM_OF_FUNCTIONS = 6;
using namespace std;
class Time//вспомогательный класс для времени
{
private:
	short int hours;
	short int minutes;
public:
	Time():hours(0), minutes(0) {};
	Time(short int hours, short int minutes=0):hours(hours), minutes(minutes) {
	};
	Time(const Time &other):
		hours(other.hours),
		minutes(other.minutes) 
	{};
	~Time() {};
	void operator=(const Time &other) {
		if (this!=&other) return;
		hours=other.hours;
		minutes=other.minutes;
	};
	short int getHours() {
		return hours;
	}
	short int getMinutes() {
		return minutes;
	}
	int setHours(short int myHours=0) {
		if (myHours<0 || myHours>23) return 1;
		hours=myHours;
		return 0;
	}
	int setMinutes(short int myMinutes=0) {
		if (myMinutes<0 || myMinutes>59) return 1;
		minutes=myMinutes;
		return 0;
	}
	friend ostream& operator<<(ostream &myStream, Time &tmp) {
		if (tmp.hours<=9) cout<<'0';
		cout<<tmp.hours<<':';
		if (tmp.minutes<=9) cout<<'0';
		cout<<tmp.minutes;
		return myStream;
	};
	void printTime() {
		if (hours<=9) cout<<'0';
		cout<<hours<<':';
		if (minutes<=9) cout<<'0';
		cout<<minutes;
	};
};
class AirFlight
{
private:
	unsigned int long flightId;
	char* destination;
	Time departureTime;
	unsigned int numOfseatsAvailable;
public:
	AirFlight():
		flightId(0),
		destination(nullptr),
		departureTime(0),
		numOfseatsAvailable()
	{};
	AirFlight(unsigned int long myFlightId, char* myDestination, Time DepartureTime=Time(), unsigned int myNumOfseatsAvailable=0):
		flightId(myFlightId),
		destination(nullptr),
		departureTime(),
		numOfseatsAvailable(myNumOfseatsAvailable)
	{
		destination = new char[strlen(myDestination)+1];
		strcpy(destination,myDestination);
	};
	AirFlight(const AirFlight &other):
		flightId(other.flightId),
		destination(nullptr),
		departureTime(other.departureTime),
		numOfseatsAvailable(other.numOfseatsAvailable)
	{
		destination = new char[strlen(other.destination)+1];
		strcpy(destination,other.destination);
	};
	~AirFlight() {
		delete[] destination;
	};
	void operator=(const AirFlight &other) {
		if (this==&other) return;
		delete[] destination;
		destination = new char[strlen(other.destination)+1];
		strcpy(destination,other.destination);
		flightId=other.flightId;
		departureTime=other.departureTime;
		numOfseatsAvailable=other.numOfseatsAvailable;
	};
	friend ostream& operator<<(ostream &myStream, AirFlight &tmp) {
			cout<<"Номер рейса: "<<tmp.flightId<<" | Пункт назначения: "<<tmp.destination<<" | Время вылета: "<<tmp.departureTime<<" | Количество свободных мест: "<<tmp.numOfseatsAvailable<<endl;
			return myStream;
	};
	int setFlightId(unsigned int long myFlightId) {
		if (myFlightId<0) return 1;
		flightId=myFlightId;
		return 0;
	};
	int setDestination(char* myDestination) {
		if (destination==myDestination) return 1;
		delete[] destination;
		destination = new char[strlen(myDestination)+1];
		strcpy(destination,myDestination);
		return 0;
	};
	int setDepartureTime(Time myDepartureTime) {
		departureTime=myDepartureTime;
		return 0;
	};
	int setNumOfseatsAvailable(unsigned int myNumOfseatsAvailable) {
		if (myNumOfseatsAvailable<0 || myNumOfseatsAvailable>MAX_NUM_OF_SEATS)
		numOfseatsAvailable=myNumOfseatsAvailable;
		return 0;
	};
	unsigned int long getFlightId() {
		return flightId;
	};
	char* getDestination() {
		return destination;
	};
	Time getDepartureTime() {
		return departureTime;
	};
	unsigned int getNumOfseatsAvailable() {
		return numOfseatsAvailable;
	};
	void printInfo() {
		cout<<"ИНФОРМАЦИЯ ОБ АВИАРЕЙСЕ №"<<flightId<<endl;
		cout<<"Пункт назначения: "<<destination<<endl;
		cout<<"Время вылета: "<<departureTime<<endl;
		cout<<"Количество свободных мест: "<<numOfseatsAvailable<<endl;
	};
	int giveTicket(unsigned int numOfTickets) {
		if (numOfseatsAvailable<numOfTickets) return 1;
		numOfseatsAvailable-=numOfTickets;
		return 0;
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	AirFlight Flights[N];
	system("pause");
	return 0;
}