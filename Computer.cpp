#include <iostream>
#include <iomanip>
#include "Computer.h"

using namespace std;

computer::computer()
	:RF(0,2,4,6,8),cycleTime(0),decodeNumber(0),RAT(5),RS(),ALU1(),ALU2()
{
	string a, b, c, d;
	while (cin >> a >> b >> c >> d)
		instructions.push_back(instruction(a, b, c, d));
}
const bool computer::check()
{
	if (instructions.size() > decodeNumber)//還未解碼完
		return false;
	if (!RAT.isAllNull()) //RS裡還有指令尚未執行
		return false;
	if (!RS.isAllNull())
		return false;
	if (ALU1.isUsing)//ALU還沒執行完畢
		return false;
	if (ALU2.isUsing)//ALU還沒執行完畢
		return false;
	return true;
}
void computer::cycle()
{
	if (instructions.size() <= decodeNumber)
		;
	else if (RS.decode(instructions[decodeNumber],decodeNumber,RF,RAT,cycleTime) != -1)//放入RS成功，decodeNumber++
		decodeNumber++;

	//ALU 是否正在用
	if (!ALU1.isUsing)
		ALU1.loadStation(RS.drop(1,cycleTime));
	else
		ALU1.cycleALU(RF, RS, RAT);

	if (!ALU2.isUsing)
		ALU2.loadStation(RS.drop(2,cycleTime));
	else
		ALU2.cycleALU(RF,RS,RAT);

	cycleTime++;
}
void computer::output()
{
	cout << "==============================================================" << endl;
	//======================================RF==============================================
	cout << "Cycle: " << cycleTime << endl
		<< "   _ RF __" << endl
		<< "F1 |" << setw(4) << RF.num[0] << " |" << endl
		<< "F2 |" << setw(4) << RF.num[1] << " |" << endl
		<< "F3 |" << setw(4) << RF.num[2] << " |" << endl
		<< "F4 |" << setw(4) << RF.num[3] << " |" << endl
		<< "F5 |" << setw(4) << RF.num[4] << " |" << endl
		<< "   --------" << endl << endl;

  	RAT.outputRAT();
	RS.outputRS1();
	ALU1.outputALU();
	
 	RS.outputRS2();
	ALU2.outputALU();
}