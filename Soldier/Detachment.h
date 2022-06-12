#pragma once
#include "Soldier.h"
#include "MyContainer.h"
#include <algorithm>
//#include <fstream>
struct ResultBattle
{
public:
	bool isWin = false; //���� ������ 1, ��������� 0
	int countDead = 0;
	int countWounded = 0;
	ResultBattle(bool isWin, int countDead, int countWounded);
};

class Detachment
{
public:
	int GetCountSoldier(); //����� ��������� ���������� ������ � ������
	void AddSoldier(); //����� ���������� ������� � �����
	void RemoveSoldier(); //����� ���������� ������� �� ������
	void RemoveDeadSoldier(); //����� ���������� �� ������ ������ ������
	void AccountResult(ResultBattle result); //����� ����� ����������� ���
	int GetCountWin() const; //�������� ���������� ����� ������
	int GetCountLouse() const; //�������� ���������� ��������� ������
	void PrintInfo(); //����� ������ ���������� � ���� ��������
	void Sort(); //����� ������������ ������ ������ �� ���
	int GetCountLiveSoldier(); // ����� �������� ������ � �����
	//string getData();
	//void writeDetachmentToFile(string&);
private:
	myContainer<Soldier> soldiers;
	//vector<Soldier> soldiers;
	int countWin = 0;
	int countLouse = 0;
};
