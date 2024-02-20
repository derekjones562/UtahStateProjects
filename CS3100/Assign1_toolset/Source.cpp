#include"toolset.h"
#include<iostream>

int main()
{
	std::vector<double> testC;
	testC.push_back(1);
	testC.push_back(4);
	testC.push_back(6);
	testC.push_back(9);
	testC.push_back(2);
	testC.push_back(7);
	std::cout<< "Average:" <<averageOfContainer<double>(testC) << std::endl;
	std::cout<<"Standard Diviation:" << standardDiviation(testC)<< std::endl;
	std::cout<<"Timing of sd: " << timingOfFunction(standardDiviation(testC)) << std::endl;
	std::cout<<"Average timing of sd: "<<averageTime(standardDiviation(testC)) << std::endl;

	return 0;
}