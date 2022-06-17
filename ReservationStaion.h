#pragma once

#ifndef RESERVATION_STATION_H
#define RESERVATION_STATION_H

#include <iostream>
#include "Instruction.h"
#include "RegisterAllocationTable.h"

class station
{
public:
	bool isUsing;
	int type;
	int num1, num2;//register，實際對應到的值
	int order;

	int CycleTime;//如果與執行時間相同，表示這個是剛進入的指令，不能馬上做
	int registerNumber;
	int stationNumber;
	RegisterAllocation ra1, ra2;

	station();//default all -1, ra1 ra2 is default
	void saveInStation(const int stationNumber, const instruction ins,const int order, registerTemp& RF, RegisterAllocationTable& RAT,const int cycletime);
	const bool updateStation(const int number, const int order);//ALU做完後，獲得一個order 需要更新ra1,ra2
};

class ReservationStation
{
private:
	station s1[5];//need manage
public:
	ReservationStation();
	const int decode(const instruction ins, const int order, registerTemp& RF, RegisterAllocationTable& RAT,const int cycletime);
	//解碼，放入暫存站，station要記住order，方便最後代換，成功return rat(0~4),沒放進去return -1，需要RF跟RAT做參考
	const int chooseStation(const int type);//根據type選擇使用的station
	const station drop(const int ALUType, const int cycletime);//RS根據ALU類型，選擇一個指令給ALU做運算
	void updateRS(const int number, const int order);
	const bool isAllNull();
	void outputRS1();
	void outputRS2();
};

#endif