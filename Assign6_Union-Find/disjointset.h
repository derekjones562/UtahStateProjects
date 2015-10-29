#include<iostream>
#include<fstream>
#include<string>


using namespace std;


//*****************************************************
//                 public functions
//*****************************************************
//int find(int a);									--->	returns 0 if in first set and 1 if in second set and -1 if not found
//void filein(string filename, ifstream ifile);		--->
//void ask(int a, int b);							--->	prints out response to question: are they in the same school?
//disjoint();					-->	constructor. colection to numbers 1 - 1000. sets everything else to -1
//~disjoint();					-->	deconstructor
//
//*****************************************************
//                 private functions
//******************************************************
//
//void join(int a, int b);				--> union fuction
//void insert(int a, int b)				--> inserts a into sets b
//void tempInsert(int a, int b)			--> inserts a and b  into uknownsets 
//bool checkForBadData(int a, int b)	--> returns true of they are in the same set. function used if the file gives conflicting data
//void askunknownsets(int a, int b)		--> prints out respones to question are they in the same school but for the unknown sets
//



const int SIZE = 1000;

class disjoint
{
public:
	
	int find(int a)
	{
		int found = -1;
		bool earlybreak =false; //set to true if you reach -1 on both sets
		for(int i =0; i < size; i++)
		{
			for(int j=0; j< 2; j++)
			{
				if(sets[j][i] == a)
					found = j;
				if((j+1)%2 == 0)
				if(sets[j][i] == -1 && sets[j-1][i] == -1)
				{
					earlybreak = true;
				}
			}
			if(earlybreak == true)
				break;
		}
		return found;
	}


	void filein(string filename, ifstream &ifile)
	{
		char input;
		int a, b;
		ifile >>input>>a>>b;
		if(input == 'D' || input == 'd')
		{
			if(checkForBadData(a,b))
			{
				cout<<"Different " <<a<<" "<<b<<":  BAD DATA\n";
			}
			else
			{
				notjoinedwith[a-1] = pathcompression(b);
				notjoinedwith[b-1] = a;
			}
		}
		if(input == 'A' || input == 'a')
		{
			ask(a, b);
		}
	}


	void ask(int a, int b)
	{
		int first = find(a), second = find(b);
		if(first == -1 || second == -1)
		{
			//needsomethinghere;
			
		}
		else if(first == second)
		{
			cout<<"Person "<<a<<"and "<<b<<":  Went to the same school.\n";
		}
		else if(first != second)
		{
			cout<<"Person "<<a<<"and "<<b<<":  In different schools.\n";
		}
	}
	disjoint(int s=SIZE)
	{
		size = s;
		for(int i = 0; i < size; i++)
		{
			collection[i] = i+1;
			notjoinedwith[i] = -1;
			for(int j = 0; j<2; j++)
			{
				sets[j][i] = -1;
			}
		}
	}
	~disjoint()
	{}
private:
	int size; //number of total people in collection
	int collection[SIZE];
	int notjoinedwith[SIZE];
	int sets[2][SIZE];


	


	void join(int a, int b)
	{
		switch(find(a))
		{
		case -1:
			switch(find(b))
			{
			case -1://if both not in a set put in first set
				insert(a, 0);
				insert(b, 0);
				break;
			case 0:
				insert(a, 0);
				break;
			case 1:
				insert(a, 1);
				break;
			}
			break;
		case 0:
			insert(b, 0);
			break;
		case 1:
			insert(b, 1);
			break;
		}
	}

	void insert(int a, int b)
	{
		//search until empty slot then put in empty slot
		int i = 0;
		while(sets[b][i] != -1)
		{
			i++;
		}
		sets[b][i] = a;
		
	}
	
	bool checkForBadData(int a, int b)
	{
		bool isbaddata = false;
		int first = find(a);
		if(first != -1 && first == find(b))
			isbaddata = true;
		return isbaddata;
	}
	bool setsisEmpty()
	{
		return(sets[0][0] == -1);
	}

	int pathcompression(int b)
	{
		if(notjoinedwith[b-1] == -1)
			return b;
		if(sets[b-1][b-1] != b)
		return pathcompression(notjoinedwith[b-1]);
	}

	
};