#include<iostream>
#include"Instruction.h"

using namespace std;

instruction::instruction(const string a,const string b,const string c,const string d)
{
	int tmpa = 0;
	int tmpb = stoi(b.substr(1, 1)) - 1;
	int tmpc = stoi(c.substr(1, 1)) - 1;
	int tmpd = 0;
	if (a.find("ADDI") != -1)
	{
		tmpa = 0;
		tmpd = stoi(d);
		init(tmpa, tmpb, tmpc, tmpd);
	}
	else if (a.find("ADD") != -1)
	{
		tmpa = 1;
		tmpd = stoi(d.substr(1, 1)) - 1;
		init(tmpa, tmpb, tmpc, tmpd);

	}
	else if (a.find("SUB") != -1)
	{
		tmpa = 2;
		tmpd = stoi(d.substr(1, 1)) - 1;
		init(tmpa, tmpb, tmpc, tmpd);
	}
	else if (a.find("MUL") != -1)
	{
		tmpa = 3;
		tmpd = stoi(d.substr(1, 1)) - 1;
		init(tmpa, tmpb, tmpc, tmpd);
	}
	else if (a.find("DIV") != -1)
	{
		tmpa = 4;
		tmpd = stoi(d.substr(1, 1)) - 1;
		init(tmpa, tmpb, tmpc, tmpd);
	}
	else
	{
		cout << "Instrucion constructor ERROR" << endl;
		exit(1);
	}
}
void instruction::init(const int a,const int b,const int c,const int d)
{
	type = a;
	r1 = b;
	r2 = c;
	r3 = d;
}

registerTemp::registerTemp(const int num1, const int num2, const int num3, const int num4, const int num5)
{
	for (int i = 0; i < 5; i++)
	{
		order[i] = -1;
	}
	num[0] = num1;
	num[1] = num2;
	num[2] = num3;
	num[3] = num4;
	num[4] = num5;
}
const bool registerTemp::saveNumberInRegister(const int index,const int num,const int order)
{
	if (this->order[index] <= order)
	{
		this->num[index] = num;
 		return true;
	}
	return false;
}