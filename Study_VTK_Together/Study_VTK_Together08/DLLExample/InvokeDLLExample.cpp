#include "DLLExample.h"
#include <iostream>

int main()
{
	std::cout<<"If you give me two integer numbers, and I can calculate their Add result:"<<std::endl;

	int num1 = 0, num2 = 0;

	std::cin>>num1>>num2;

	std::cout<<"The result is: "<<add(num1,num2)<<std::endl;

	return 0;
}