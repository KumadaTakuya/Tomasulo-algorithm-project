#include <iostream>
#include <iomanip>

#include "Instruction.h"
#include "ReservationStaion.h"

using namespace std;

station::station()
	:isUsing(false),order(-1),type(-1),num1(-1),num2(-1),ra1(),ra2(),registerNumber(-1),stationNumber(-1),CycleTime(-1)
{

}
void station::saveInStation(const int stationNumber,const instruction ins,const int order, registerTemp& RF, RegisterAllocationTable& RAT,const int cycletime)
{
	isUsing = true;
	this->stationNumber = stationNumber;
	this->registerNumber = ins.r1;
	this->CycleTime = cycletime;

	if (ins.type == 0)
		type = 1;
	else
		type = ins.type;
	this->order = order;
	//先看RAT，有則用，沒用就使用RF，然後更新RAT
	if (RAT.search(ins.r2).isSavingRS)//正在被使用
		ra1 = RAT.search(ins.r2);
	else//沒被使用，直接取用register
		num1 = RF.num[ins.r2];

	if (ins.type == 0)
		num2 = ins.r3;
	else if (RAT.search(ins.r3).isSavingRS)//正在被使用
		ra2 = RAT.search(ins.r3);
	else//沒被使用，直接取用register
		num2 = RF.num[ins.r3];	
}
const bool station::updateStation(const int number,const int order)
{
	if (ra1.update(order))
	{
		num1 = number;
		if (ra2.update(order))
		{
			num2 = number;
		}
		return true;
	}
	if (ra2.update(order))
	{
		num2 = number;
		return true;
	}
	return false;
}


ReservationStation::ReservationStation()
{
	s1[0] = station();
	s1[1] = station();
	s1[2] = station();
	s1[3] = station();
	s1[4] = station();
}
const int ReservationStation::decode(const instruction ins, const int order, registerTemp& RF,RegisterAllocationTable& RAT,const int cycletime)
{
	int stationNumber = chooseStation(ins.type);
	if (stationNumber != -1)
	{
		s1[stationNumber].saveInStation(stationNumber,ins,order,RF,RAT,cycletime);
		//update RAT
		RAT.saveReservationStationNumber(ins.r1, stationNumber ,order);
		return stationNumber;
	}
	return -1;
}
const int ReservationStation::chooseStation(const int type)
{
	switch (type)
	{
	case 0:
	case 1:
	case 2:
		if (!s1[0].isUsing)
			return 0;
		if (!s1[1].isUsing)
			return 1;
		if (!s1[2].isUsing)
			return 2;
		break;
	case 3:
	case 4:
		if (!s1[3].isUsing)
			return 3;
		if (!s1[4].isUsing)
			return 4;
		break;
	}
	return -1;
}
const station ReservationStation::drop(const int ALUType,const int cycletime)
{
	station tmp;
	if (ALUType == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			if (s1[i].isUsing && s1[i].CycleTime != cycletime && s1[i].num1 != -1 && s1[i].num2 != -1)//確保num數字都有到，cycletime不一樣
			{
				tmp = s1[i];
				s1[i].isUsing = false;
				return tmp;
			}
		}
	}
	else if (ALUType == 2)
	{
		for (int i = 3; i < 5; i++)
		{
			if (s1[i].isUsing && s1[i].CycleTime != cycletime && s1[i].num1 != -1 && s1[i].num2 != -1)
			{
				tmp = s1[i];
				s1[i].isUsing = false;
				return tmp;
			}
		}
	}
	else
	{
		cout << "RS drop error" << endl;
		exit(1);
	}
	return tmp;//return station is defalut
}
void ReservationStation::updateRS(const int number, const int order)
{
	for (int i = 0; i < 5; i++)
		s1[i].updateStation(number, order);
}
const bool ReservationStation::isAllNull()
{
	for (int i = 0; i < 5; i++)
	{
		if (s1[i].isUsing)
			return false;
	}
	return true;
}
void ReservationStation::outputRS1()
{
	cout << "    _ RS -----------------" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "RS" << i + 1 << " |" << setw(5);
		if (s1[i].isUsing)
		{
			switch (s1[i].type)
			{
			case 1:
				cout << "+";
				break;
			case 2:
				cout << "-";
				break;
			case 3:
				cout << "*";
				break;
			case 4:
				cout << "/";
				break;
			default:
				cout << "RS output is error" << endl;
				exit(1);
			}
		}
		else
			cout << " ";

		cout << " |";
		if (!s1[i].isUsing)
			cout << setw(5) << " ";
		else if (s1[i].num1 != -1)
			cout << setw(5) << s1[i].num1;
		else
			cout << "  RS" << s1[i].ra1.getRSNumber() + 1;
		cout << " |";

		if (!s1[i].isUsing)
			cout << setw(5) << " ";
		else if (s1[i].num2 != -1)
			cout << setw(5) << s1[i].num2;
		else
			cout << "  RS" << s1[i].ra2.getRSNumber() + 1;
		cout << " |" << endl;
	}
	cout << "    ----------------------" << endl;
}
void ReservationStation::outputRS2()
{
	cout << "    _ RS -----------------" << endl;
	for (int i = 3; i < 5; i++)
	{
		cout << "RS" << i + 1 << " |" << setw(5);
		if (s1[i].isUsing)
		{
			switch (s1[i].type)
			{
			case 1:
				cout << "+";
				break;
			case 2:
				cout << "-";
				break;
			case 3:
				cout << "*";
				break;
			case 4:
				cout << "/";
				break;
			default:
				cout << "RS output is error" << endl;
				exit(1);
			}
		}
		else
			cout << " ";

		cout << " |";
		if (!s1[i].isUsing)
			cout << setw(5) << " ";
		else if (s1[i].num1 != -1)
			cout << setw(5) << s1[i].num1;
		else
			cout << "  RS" << s1[i].ra1.getRSNumber() + 1;
		cout << " |";

		if (!s1[i].isUsing)
			cout << setw(5) << " ";
		else if (s1[i].num2 != -1)
			cout << setw(5) << s1[i].num2;
		else
			cout << "  RS" << s1[i].ra2.getRSNumber() + 1;
		cout << " |" << endl;
	}
	cout << "    ----------------------" << endl;
}