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
	int cycleTime;//�ثe�O�ĴX��Cycle
	int decodeNumber;//�ĴX��instructions���J��RS
	vector<instruction> instructions;
	RegisterAllocationTable RAT;
	ReservationStation RS;//�]�t0~4���Ȧs
	ArithmetricLogicUnit ALU1,ALU2;//�]�tALU1,ALU2�AALU����������U���J
public:
	computer();//��l�ƪ���A���Jinstructions
	const bool check();//�O�_�Ҧ��ʧ@�w���槹��
	void cycle();//����@�Ӵ`��
	void output();//��X�зǿ�X
};
#endif // !COMPUTER_H
