#include <iostream>

#include "Computer.h"

using namespace std;

int main()
{
	computer c;
	while (!c.check())
	{
		c.cycle();
		c.output();
		//system("pause");
	}
	return 0;
}