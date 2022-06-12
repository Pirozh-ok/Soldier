#pragma once
#include "Soldier.h"
#include "MyContainer.h"
#include <algorithm>
//#include <fstream>
struct ResultBattle
{
public:
	bool isWin = false; //если победа 1, поражение 0
	int countDead = 0;
	int countWounded = 0;
	ResultBattle(bool isWin, int countDead, int countWounded);
};

class Detachment
{
public:
	int GetCountSoldier(); //метод получения количества солдат в отряде
	void AddSoldier(); //метод добавления солдата в отряд
	void RemoveSoldier(); //метод исключения солдата из отряда
	void RemoveDeadSoldier(); //метод исключения из отряда убитых солдат
	void AccountResult(ResultBattle result); //метод учёта результатов боя
	int GetCountWin() const; //получить количество побед отряда
	int GetCountLouse() const; //получить количество поражений отряда
	void PrintInfo(); //метод вывода информации о всех солдатах
	void Sort(); //метод упорядочения отряда солдат по фио
	int GetCountLiveSoldier(); // метод подсчёта солдат в строю
	//string getData();
	//void writeDetachmentToFile(string&);
private:
	myContainer<Soldier> soldiers;
	//vector<Soldier> soldiers;
	int countWin = 0;
	int countLouse = 0;
};
