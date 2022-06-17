#include <iostream>

#include "ArithmeticLogicUnit.h"

using namespace std;

ArithmetricLogicUnit::ArithmetricLogicUnit()
	:isUsing(false), executionTime(-1), exeInstruction()
{

}

const bool ArithmetricLogicUnit::loadStation(const station exeInstruction)
{
	if (isUsing)
		return false;
	if (exeInstruction.num1 != -1 && exeInstruction.num2 != -1)
	{
		isUsing = true;
		this->exeInstruction = exeInstruction;
		return true;
	}
	return false;
}
const bool ArithmetricLogicUnit::cycleALU(registerTemp& RF, ReservationStation& RS, RegisterAllocationTable& RAT)
{
	executionTime++;
	if (executionTime >= ArithmetricTime[exeInstruction.type - 1])
	{
		//ÂÐ»\°ÝÃD?
		switch (exeInstruction.type)
		{
		case 1:
			RF.saveNumberInRegister(exeInstruction.registerNumber, exeInstruction.num1 + exeInstruction.num2,exeInstruction.order);
			break;
		case 2:
			RF.saveNumberInRegister(exeInstruction.registerNumber, exeInstruction.num1 - exeInstruction.num2, exeInstruction.order);
			break;
		case 3:
			RF.saveNumberInRegister(exeInstruction.registerNumber, exeInstruction.num1 * exeInstruction.num2, exeInstruction.order);
			break;
		case 4:
			RF.saveNumberInRegister(exeInstruction.registerNumber, exeInstruction.num1 / exeInstruction.num2, exeInstruction.order);
			break;
		default:
			cout << "ALU cycle is error" << endl;
			exit(1);
		}

		RAT.updateTable(exeInstruction.order);
		RS.updateRS(RF.num[exeInstruction.registerNumber], exeInstruction.order);
		isUsing = false;
		exeInstruction = station();
		executionTime = 0;
		return true;
	}
	return false;
}
void ArithmetricLogicUnit::outputALU()
{
	cout << "BUFFER: ";
	if (isUsing)
	{
		cout << "(RS" << exeInstruction.stationNumber + 1 << ") " << exeInstruction.num1 << " ";
		switch (exeInstruction.type)
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
			cout << "output ALU is error" << endl;
			exit(1);
		}
		cout << " " << exeInstruction.num2;
	}
	else
		cout << "empty";
	cout << endl << endl;
}