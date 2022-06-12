#pragma once
#include "Detachment.h"
#include <algorithm>

int Detachment::GetCountSoldier()
{
	return soldiers.size();
}

//����� ���������� �������
void Detachment::AddSoldier()
{
	Soldier s;
	s.EnterData();

	for (int i = 0; i < soldiers.size(); i++)
		if (s.GetName() == soldiers[i].GetName() || s.GetNumber() == soldiers[i].GetNumber())
			throw exception("������ � ����� ������ ��� ������� ��� ���� � ������!");

	soldiers.push_back(s);
	cout << "������ ��� �������� � �����!" << endl;
}

//����� �������� ������� �� ����� � ������
void Detachment::RemoveSoldier()
{
	string name;
	int number;

	cout << "������� ��� �������, �������� ������ ���������: ";
	cin.ignore(cin.rdbuf()->in_avail()); //������� �������� ������
	getline(cin,name);
	cout << "������� ����� �������, �������� ������ ���������: ";
	cin.ignore(cin.rdbuf()->in_avail()); //������� �������� ������
	cin >> number;
	
	for (int i = 0; i < soldiers.size(); i++)
	{
		if (soldiers[i].GetName() == name && soldiers[i].GetNumber() == number)
		{
			soldiers.erase(i);
			cout << "������ ��� ��������!" << endl;
			return;
		}
	}
	cout << "������� � ����� ������ � ������ �� ����������!" << endl;
}

//����� �������� ���� ������ ������
void Detachment::RemoveDeadSoldier()
{
	if (soldiers.size() > 0)
	{
		//���������� �� ���� �������� � ������� ���, � ���� ������ - ����
		for (int i = 0; i < soldiers.size(); i++)
		{
			if (soldiers[i].GetCondition() == "����")
			{
				soldiers.erase(i);
				i--;
			}
		}
		cout << "��� ������ ������� ��������� �� ������!" << endl;
	}
	else cout << "� ������ ��� ��� ������!" << endl;
}

//����� ����� ����������� ��������
void Detachment::AccountResult(ResultBattle result)
{
	//���� ������, �� ��������� ������� ������� ������, � ������������ ����� ��������� �������� �������� ����������� �����
	if (result.isWin)
	{
		countWin++;

		for (int i = 0, j = 0, k = 0; i < soldiers.size(); i++)
		{
			if (j < result.countWounded && soldiers[i].GetCondition() == "� �����")
			{
				soldiers[i].AddWin(Condition::Wounded);
				j++;
			}
			else if (k < result.countDead && soldiers[i].GetCondition() == "� �����")
			{
				soldiers[i].AddWin(Condition::Dead);
				k++;
			}
			else soldiers[i].AddWin(Condition::In_the_ranks);
		}
	}
	//����� ����������� ��������� � ����� ����� ��������� ������
	else
	{
		countLouse++;

		for (int i = 0, j = 0, k = 0; i < soldiers.size(); i++)
			if (j < result.countWounded)
			{
				soldiers[i].AddLouse(Condition::Wounded);
				j++;
			}
			else if (k < result.countDead)
			{
				soldiers[i].AddLouse(Condition::Dead);
				k++;
			}
			else soldiers[i].AddLouse(Condition::In_the_ranks);
	}
	cout << "���������� �������� ������ ������!" << endl;
}

//����� ��������� ���������� ����� ������
int Detachment::GetCountWin() const
{
	return countWin;
}

//����� ��������� ���������� ��������� ������
int Detachment::GetCountLouse() const
{
	return countLouse;
}

//����� ������ ���������� �� ������
void Detachment::PrintInfo()
{
	if (soldiers.size() < 1)
	{
		cout << "� ������ ��� ��� ������!" << endl;
		return;
	}

	Sort();

	cout << "���������� ����� ������: " << countWin << endl;
	cout << "���������� ��������� ������: " << countLouse << endl;
	cout << "� ������ ���������� "<< soldiers.size() << " ������: " << endl;
	for (int i = 0; i < soldiers.size(); i++)
	{
		cout << i + 1;
		soldiers[i].PrintData();
		cout << endl;
	}
}

struct myclass {
	bool operator() (Soldier i, Soldier j) { return (i.GetName() < j.GetName()); }
} myobject;

//����� ���������� ������ �� �����
void Detachment::Sort()
{
	sort(soldiers.begin(), soldiers.end(), myobject);
}

//����� ��������� ���������� ����� ������ � ������
int Detachment::GetCountLiveSoldier()
{
	int count = 0;

	for (int i = 0; i < soldiers.size(); i++)
	{
		if (soldiers[i].GetCondition() == "� �����")
			count++;
	}

	return count; 
}

//����� ������ ������ � ����
void Detachment::WriteToFile()
{
	ofstream file("data.txt");

	if (!file.is_open())
	{
		cout << "�� ������� ������� ���� data.txt" << endl;
		return;
	}

	file.clear();

	file << to_string(countWin) << endl;
	file << to_string(countLouse) << endl;
	for (int i = 0; i < soldiers.size(); i++)
	{
		file << soldiers[i].GetName() << endl;
		file << soldiers[i].GetNumber() << endl;
		file << soldiers[i].GetRangInt() << endl;
		file << soldiers[i].GetMorale() << endl;
		file << soldiers[i].GetCountWin() << endl;
		file << soldiers[i].GetCountLouse() << endl;
		file << soldiers[i].GetConditionInt() << endl;
	}

	file.close();
	cout << "������ ������� �������� � ���� data.txt" << endl;
}

//����� ���������� ������ �� �����
void Detachment::ReadFromFile()
{
	ifstream file("data.txt");

	if (!file.is_open())
	{
		cout << "�� ������� ������� ���� data.txt" << endl;
		return;
	}

	soldiers.clear();
	string s;
	getline(file, s);
	countWin = stoi(s);
	getline(file, s);
	countLouse = stoi(s);

	while (file.good())
	{
		string name;
		getline(file, name);
		getline(file, s);
		int number = stoi(s);
		getline(file, s);
		int rank = stoi(s);
		getline(file, s);
		int morale = stoi(s);
		getline(file, s);
		int countWin = stoi(s);
		getline(file, s);
		int countLouse = stoi(s);
		getline(file, s);
		int condition = stoi(s);
		if (name != "")
		{
			Soldier newSoldier(name, number, rank, morale, countWin, countLouse, condition);
			soldiers.push_back(newSoldier);
		}
	}

	file.close();
	cout << "������ ������� ��������!" << endl;
}

// ���������� ���������� ���
ResultBattle::ResultBattle(bool _isWin, int _countDead, int _countWounded)
{
	isWin = _isWin;
	countDead = _countDead;
	countWounded = _countWounded;
}

