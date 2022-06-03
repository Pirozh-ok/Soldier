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
	void SetDefaultData(); //����� ��������� ��������� ��������
public:
	Soldier(); //����������� �� ���������
	Soldier(string _fullName, int _number);  // ����������� � ����������� ���, �����
	void EnterData(); // ����� ����� ������
	void PrintData() const; //����� ������ ������
	string GetName() const; // ����� ��������� �����
	string GetRank() const; // ����� ��������� ������
	int GetMorale() const; // ����� ��������� ������
	void UpRank(); // ����� ��������� �����
	void DownRank(); // ����� ��������� �����
	int GetCountWin() const; // ����� ��������� ��������� �����
	void AddWin(Condition newCondition); // ����� ���������� ������
	int GetCountLouse() const; // ����� ��������� ���������� ���������
	void AddLouse(Condition newCondition); // ����� ���������� ���������
	string GetCondition() const; // ����� ��������� ���������
	int GetNumber() const; // ����� ��������� ������
	void Heal(); // ����� ������� �������
};