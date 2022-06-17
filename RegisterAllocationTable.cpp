#include<iostream>
#include <iomanip>
#include "RegisterAllocationTable.h"

using namespace std;

RegisterAllocation::RegisterAllocation()
	:RSNumber(-1),InstructionOrder(-1),isSavingRS(false)
{

}
const bool RegisterAllocation::saveAllocationNumber(const int RSNumber, const int order)
{
	if (this->InstructionOrder < order)//ÂÐ»\
	{
		this->RSNumber = RSNumber;
		InstructionOrder = order;
		isSavingRS = true;
		return true;
	}
	return false;
}
const bool RegisterAllocation::update(const int order)
{
	if (isSavingRS && this->InstructionOrder == order)
	{
		this->RSNumber = -1;
		InstructionOrder = -1;
		isSavingRS = false;
		return true;
	}
	return false;
}
const int RegisterAllocation::getRSNumber()
{
	return RSNumber;
}
const int RegisterAllocation::getOrder()
{
	return InstructionOrder;
}

RegisterAllocationTable::RegisterAllocationTable(const int size)
	: size(size)
{
	table.resize(size);
}
const bool RegisterAllocationTable::saveReservationStationNumber(const int registerNumber, const int RSNumber, const int order)
{
	if (table[registerNumber].saveAllocationNumber(RSNumber, order))
		return true;
	return false;
}
const bool RegisterAllocationTable::updateTable(const int order)
{
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		if (table[i].update(order))
			flag = true;
	}
	if (flag)
		return true;
	return false;
}
const RegisterAllocation RegisterAllocationTable::search(const int registerNumber)
{
	for (int i = 0; i < size; i++)
	{
		if (table[i].isSavingRS && i == registerNumber)
			return table[i];
	}
	RegisterAllocation tmp;
	return tmp;
}
void RegisterAllocationTable::outputRAT()
{
	cout << "   _ RAT __" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "F" << i + 1 << " |";
		if (table[i].isSavingRS)
			cout << "  " << "RS" << table[i].RSNumber + 1<< " |" << endl;
		else
			cout << setw(5) << " " << " |" << endl;
	}
	cout << "   ---------" << endl << endl;
}
const bool RegisterAllocationTable::isAllNull()
{
	for (int i = 0; i < size; i++)
	{
		if(table[i].isSavingRS)
			return false;
	}
	return true;
}