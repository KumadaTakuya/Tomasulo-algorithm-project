#pragma once

#ifndef REGISTER_ALLOCATION_H
#define REGISTER_ALLOCATION_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;
class RegisterAllocation
{
private:
	int InstructionOrder;//該RAT是第幾個指令產生出來的
public:
	bool isSavingRS;
	int RSNumber;//是第幾個RAT，應為0~4，如果為-1代表該RAT未生效
	RegisterAllocation();//初始化時，全部歸0，並且order-1

	const bool saveAllocationNumber(const int RSNumber,const int order);//decode後，更新RegisterAllocation，並且比較指令順序大小
	const bool update(const int order);//ALU做完後，更新RegisterAllocation(禁止參考),只有指令相同時(代表為同個指令下的RSNumber做更新)	
	const int getRSNumber();
	const int getOrder();
};

class RegisterAllocationTable
{
private:
	int size;
	vector<RegisterAllocation> table;//進入0~4的RAT
	
public:
	
	RegisterAllocationTable(const int size);
	
	const bool saveReservationStationNumber(const int registerNumber,const int RSNumber,const int order);//儲存/取代reservationStationNumber
	const bool updateTable(const int order);//ALU計算完後會呼叫這個程式，會把相同order的數字做更新(不考慮RSNUMBER，同order必同RSNUMBER)
	const RegisterAllocation search(const int registerNumber);//找尋該registerNumber是否被使用，回傳reservation station，如果沒有則回傳的RSNumber為-1
	void outputRAT();
	const bool isAllNull();
};

#endif