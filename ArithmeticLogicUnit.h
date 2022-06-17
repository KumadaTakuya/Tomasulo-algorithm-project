#pragma once

#ifndef ARITHMETRIC_LOGIC_UNIT_H
#define ARITHMETRIC_LOGIC_UNIT_H

#include <iostream>
#include "Instruction.h"
#include "ReservationStaion.h"
#include "RegisterAllocationTable.h"
using namespace std;

class ArithmetricLogicUnit
{
private:
	int executionTime;
	int ArithmetricTime[4] = { 2,2,4,8 };

	station exeInstruction;//�x�s�n���檺���O,��station����
public:
	bool isUsing;
	ArithmetricLogicUnit();

	const bool loadStation(const station exeInstruction);//���J���ORA�A�p�G�w�g�����O���b����A�h���J���ѡCstation�����|�O��ۤv�O�ĴX��station
	const bool cycleALU(registerTemp& RF, ReservationStation& RS, RegisterAllocationTable& RAT);
	//����ɶ�+1�A���槹���^��true�A�|������sRF,RAT,RS
	void outputALU();
};

#endif // !ARITHMETRIC_LOGIC_UNIT_H
