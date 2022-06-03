#pragma once
#include <iostream>
using namespace std;

enum Condition
{
	In_the_ranks,
	Wounded,
	Dead
};

enum Rank
{
	Private,
	Corporal,
	Foreman,
	Ensign,
};

class Soldier
{
private:
	string fullName;
	int number;
	Rank rank;
	int morale;
	int countWin;
	int countLouse;
	Condition condition;
	void SetDefaultData(); //метод установки начальных значений
public:
	Soldier(); //конструктор по умолчанию
	Soldier(string _fullName, int _number);  // конструктор с параметрами ФИО, номер
	void EnterData(); // метод ввода данных
	void PrintData() const; //метод вывода данных
	string GetName() const; // метод получения имени
	string GetRank() const; // метод получения звания
	int GetMorale() const; // метод получения морали
	void UpRank(); // метод повышения ранга
	void DownRank(); // метод понижения ранга
	int GetCountWin() const; // метод получения количетва побед
	void AddWin(Condition newCondition); // метод добавления победы
	int GetCountLouse() const; // метод получения количества поражений
	void AddLouse(Condition newCondition); // метод добавления поражения
	string GetCondition() const; // метод получения состояния
	int GetNumber() const; // метод получения номера
	void Heal(); // метод лечения солдата
};