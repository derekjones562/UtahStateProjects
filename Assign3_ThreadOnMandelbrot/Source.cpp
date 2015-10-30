#include<fstream>
#include<sstream>
#include<iostream>
#include<thread>
#include<vector>
#include"PPMfile.h"

int main()
{
	//generateMandelbrotSet();
	const int SQSIZE = 50;//size of the square you are looking at in number of pixels
	const int maxV =15;//color "magic number according to http://netpbm.sourceforge.net/doc/ppm.html
	std::stringstream ss;
	//std::vector<std::vector<int>> mbrotset;
	//std::vector<int> lineofPixels(SQSIZE);
	std::fstream fout;
	std::string filename="PPM.txt";
	fout.open(filename.c_str(), std::ios::out | std::ios::binary);
	//fout.open(filename);
	ss<<"P3\n"<<SQSIZE<<" "<<SQSIZE<<"\n"<<maxV<<"\n";
	

	int pixelx= SQSIZE;
	int pixely= SQSIZE/2;//2 is the number of threads generating the set. if more threads, increment accordingly
	auto t = std::thread([&](){ss<<generatePartofMbrotSet(2,0,-2,-2,pixelx, pixely,maxV);});
	auto t2 = std::thread([&](){ss<<generatePartofMbrotSet(2,2,-2,0,pixelx, pixely,maxV);});
	t.join();
	t2.join();

	fout<<ss.str();
	fout.close();
	return 0;
}