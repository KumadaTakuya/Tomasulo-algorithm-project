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
	int num1, num2;//register�A��ڹ����쪺��
	int order;

	int CycleTime;//�p�G�P����ɶ��ۦP�A��ܳo�ӬO��i�J�����O�A���న�W��
	int registerNumber;
	int stationNumber;
	RegisterAllocation ra1, ra2;

	station();//default all -1, ra1 ra2 is default
	void saveInStation(const int stationNumber, const instruction ins,const int order, registerTemp& RF, RegisterAllocationTable& RAT,const int cycletime);
	const bool updateStation(const int number, const int order);//ALU������A��o�@��order �ݭn��sra1,ra2
};

class ReservationStation
{
private:
	station s1[5];//need manage
public:
	ReservationStation();
	const int decode(const instruction ins, const int order, registerTemp& RF, RegisterAllocationTable& RAT,const int cycletime);
	//�ѽX�A��J�Ȧs���Astation�n�O��order�A��K�̫�N���A���\return rat(0~4),�S��i�hreturn -1�A�ݭnRF��RAT���Ѧ�
	const int chooseStation(const int type);//�ھ�type��ܨϥΪ�station
	const station drop(const int ALUType, const int cycletime);//RS�ھ�ALU�����A��ܤ@�ӫ��O��ALU���B��
	void updateRS(const int number, const int order);
	const bool isAllNull();
	void outputRS1();
	void outputRS2();
};

#endif