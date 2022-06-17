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
	int InstructionOrder;//��RAT�O�ĴX�ӫ��O���ͥX�Ӫ�
public:
	bool isSavingRS;
	int RSNumber;//�O�ĴX��RAT�A����0~4�A�p�G��-1�N���RAT���ͮ�
	RegisterAllocation();//��l�ƮɡA�����k0�A�åBorder-1

	const bool saveAllocationNumber(const int RSNumber,const int order);//decode��A��sRegisterAllocation�A�åB������O���Ǥj�p
	const bool update(const int order);//ALU������A��sRegisterAllocation(�T��Ѧ�),�u�����O�ۦP��(�N���P�ӫ��O�U��RSNumber����s)	
	const int getRSNumber();
	const int getOrder();
};

class RegisterAllocationTable
{
private:
	int size;
	vector<RegisterAllocation> table;//�i�J0~4��RAT
	
public:
	
	RegisterAllocationTable(const int size);
	
	const bool saveReservationStationNumber(const int registerNumber,const int RSNumber,const int order);//�x�s/���NreservationStationNumber
	const bool updateTable(const int order);//ALU�p�⧹��|�I�s�o�ӵ{���A�|��ۦPorder���Ʀr����s(���Ҽ{RSNUMBER�A�Porder���PRSNUMBER)
	const RegisterAllocation search(const int registerNumber);//��M��registerNumber�O�_�Q�ϥΡA�^��reservation station�A�p�G�S���h�^�Ǫ�RSNumber��-1
	void outputRAT();
	const bool isAllNull();
};

#endif