#include "disjointset.h"
#include<fstream>
#include<string>

using namespace std;

int main()
{
	int testcases, numberofpeople, numberoflines;
	string filename ="HighSchool.txt";
	ifstream ifile(filename);

	ifile>>testcases;
	for(int i =0; i<testcases; i++)
	{
		cout<<"\n\n\nTest case #"<<i+1<<endl;
		ifile>>numberofpeople>>numberoflines;
		disjoint djs(numberoflines);
		for(int j = 0; j < numberoflines; j++)
		{
			djs.filein(filename, ifile);
		}
	}

	ifile.close();
	return 0;
}