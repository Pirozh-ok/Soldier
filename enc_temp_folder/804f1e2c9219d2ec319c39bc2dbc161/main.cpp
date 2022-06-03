#include"Detachment.h"
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

void AddSoldiers(Detachment& d)
{
	cout << "������� ���������� ������, ������� ������ �������� � �����: ";
	int enter;
	cin >> enter;
	if (enter > 0)
		for (int i = 0; i < enter; i++)
		{
			try
			{
				d.AddSoldier();
			}
			catch(exception ex)
			{
				cout << ex.what() << endl;
			}
		}
	else cout << "���������� ������ �� ����� ���� �������������";
}

void StartBattle(Detachment& d)
{
	if (d.GetCountSoldier() > 0)
	{
		int countDead = rand() % d.GetCountSoldier();
		int countWead = rand() % (d.GetCountSoldier() - countDead);
		int r = rand() % 2;
		bool isWin = (r == 0) ? true : false;

		string result = isWin ? "������" : "���������";
		cout << "��������� ��������: " << result << ". ���������� �������� " << countWead << ", ���������� Dead�� " << countDead << endl;
		d.AccountResult(ResultBattle(isWin, countDead, countWead));
	}
	else cout << "� ������ ��� ��� ������!" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	Detachment detachment;
	int enter = 0;
	while (1)
	{
		cout << "\n�������� ������ ��������: 1 - �������� �������� � �����, 2 - ��������� ������� �� ������ �� �����, 3 - ������� ���������� �� ������, 4 - ��������� �� ������ ���� Dead�� ������, 5 - �������� �����, 0 - ����� �� ���������" << endl;
		cin >> enter;

		switch (enter)
		{
		case 0:
			return 0;

		case 1:
			AddSoldiers(detachment);
			break;
		case 2:
			detachment.RemoveSoldier();
			break;
		case 3:
			detachment.PrintInfo();
			break;
		case 4:
			detachment.RemoveDeadSoldier();
			break;
		case 5:
			StartBattle(detachment);
			break;
		default: cout << "��� �������� �� ������ ������!" << endl;
			break;
		}
	}
	return 0; 
}
