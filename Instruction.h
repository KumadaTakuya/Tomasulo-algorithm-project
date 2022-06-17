#pragma once

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>
using namespace std;

//儲存0~4 的register值
class instruction
{
public:
	int type;//0 = ADDI, 1 = ADD, 2 = SUB, 3 = MUL, 4 = DIV
	int r1;
	int r2;
	int r3;// equals immidiate
	
	instruction(const string,const string,const string,const string);//讀入字串，直接改寫成指令

	void init(const int, const int, const int, const int);//給instruction使用，幫助初始化type,a,b,c
};

class registerTemp
{
public:
	int num[5];
	int order[5];

	registerTemp(const int n1,const int n2,const int n3,const int n4,const int n5);//order = -1
	const bool saveNumberInRegister(const int index,const int num,const int order);//儲存值
};
#endif // !
