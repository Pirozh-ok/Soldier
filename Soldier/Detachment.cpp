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
	cin >> name;
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
			if (j < result.countWounded)
			{
				soldiers[i].AddWin(Condition::�����);
				j++;
			}
			else if (k < result.countDead)
			{
				soldiers[i].AddWin(Condition::����);
				k++;
			}
			else soldiers[i].AddWin(Condition::�_�����);
	}
	//����� ����������� ��������� � ����� ����� ��������� ������
	else
	{
		countLouse++;

		for (int i = 0, j = 0, k = 0; i < soldiers.size(); i++)
			if (j < result.countWounded)
			{
				soldiers[i].AddLouse(Condition::�����);
				j++;
			}
			else if (k < result.countDead)
			{
				soldiers[i].AddLouse(Condition::����);
				k++;
			}
			else soldiers[i].AddLouse(Condition::�_�����);
	}
	cout << "���������� �������� ������ ������!" << endl;
}

int Detachment::GetCountWin() const
{
	return countWin;
}

int Detachment::GetCountLouse() const
{
	return countLouse;
}

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

void Detachment::Sort()
{
	for (int i = 0; i < soldiers.size(); i++)
		for (int j = 0; j < soldiers.size() - 1; j++)
		{
			if (soldiers[j].GetName() < soldiers[j+1].GetName())
			{
				Soldier temp = soldiers[j]; 
				soldiers[j] = soldiers[j + 1];
				soldiers[j + 1] = temp;
			}
		}
}

ResultBattle::ResultBattle(bool _isWin, int _countDead, int _countWounded)
{
	isWin = _isWin;
	countDead = _countDead;
	countWounded = _countWounded;
}
