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

	station exeInstruction;//儲存要執行的指令,用station執行
public:
	bool isUsing;
	ArithmetricLogicUnit();

	const bool loadStation(const station exeInstruction);//載入指令RA，如果已經有指令正在執行，則載入失敗。station本身會記住自己是第幾個station
	const bool cycleALU(registerTemp& RF, ReservationStation& RS, RegisterAllocationTable& RAT);
	//執行時間+1，執行完畢回傳true，會幫忙更新RF,RAT,RS
	void outputALU();
};

#endif // !ARITHMETRIC_LOGIC_UNIT_H
