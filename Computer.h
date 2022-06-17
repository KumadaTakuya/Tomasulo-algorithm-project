#pragma once

#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>
#include <vector>

#include "Instruction.h"
#include "RegisterAllocationTable.h"
#include "ReservationStaion.h"
#include "ArithmeticLogicUnit.h"

using namespace std;
class computer
{
private:
	registerTemp RF;
	int cycleTime;//目前是第幾個Cycle
	int decodeNumber;//第幾行instructions載入到RS
	vector<instruction> instructions;
	RegisterAllocationTable RAT;
	ReservationStation RS;//包含0~4的暫存
	ArithmetricLogicUnit ALU1,ALU2;//包含ALU1,ALU2，ALU應該幫忙協助載入
public:
	computer();//初始化物件，載入instructions
	const bool check();//是否所有動作已執行完畢
	void cycle();//執行一個循環
	void output();//輸出標準輸出
};
#endif // !COMPUTER_H
