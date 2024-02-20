#include<fstream>
#include<sstream>
#include<iostream>
#include"PPMfile.h"

int main()
{
	//generateMandelbrotSet();
	const int SQSIZE = 50;//size of the square you are looking at in number of pixels
	int maxV =15;//color "magic number according to http://netpbm.sourceforge.net/doc/ppm.html
	std::stringstream ss;
	std::fstream fout;
	std::string filename="PPM.txt";
	fout.open(filename.c_str(), std::ios::out | std::ios::binary);
	//fout.open(filename);
	ss<<"P3\n"<<SQSIZE<<" "<<SQSIZE<<"\n"<<maxV<<"\n";
	double maxx=-.5, maxy=2;//change the starting x,y to see a different part of the set
	double minx=-.5, miny=-1;//change the starting x,y to see a different part of the set
	auto y = miny;
	for(int i =0; i<SQSIZE; i++)
	{
		auto x=minx;
		for(int j=0; j<SQSIZE; j++)
		{
			int temp = generatePartofMbSet(x, y, maxV);
			ss<<temp<<" ";
			x+=(maxx - minx)/SQSIZE;
		}
		ss<<"\n";
		y+=(maxy-miny)/SQSIZE;
	}
	fout<<ss.str();
	fout.close();
	return 0;
}