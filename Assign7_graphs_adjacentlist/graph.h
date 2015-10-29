#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<fstream>
#include<string>
#include<iostream>
#include <cctype>
#include <stack>
#include <sstream>

using namespace std;

//uses adjacentcy list to store graph

struct edge
{
	int from;
	int to;
	int weight;
	edge *nextedge;
	void setEdge(int f, int t, int w)
	{
		from = f;
		to = t;
		weight = w;
		nextedge = NULL;
	}
	void printEdge()
	{
		cout<<from<<" - "<<to<<"     "<<weight;
	}
	void printEdge(bool istrue)
	{
		cout<< static_cast<char>(from+64)<<" - " << static_cast<char> (to+64) <<"     "<<weight;
	}
};

class graphNode
{
public:
	int element;
	edge *nextedge;
	bool visited;
	graphNode()
	{
		element = -1;
		nextedge = NULL;
		visited = false;
	}
	~graphNode()
	{
	}
	void setgNode(int e, edge * ne, bool v)
	{
		element = e;
		nextedge= ne;
		visited = v;
	}

};


class graph
{
private:
	graphNode *list;
	int numofNodes, numofEdges;
	bool isletterNodes;

	void setElements(int size)
	{
		for(int i =0; i<size; i++)
		{
			list[i].element = i;
			list[i].nextedge = NULL;
		}
	}
	string convertstringalphatostringdigit(string in)
	{
		string out;
		if(in[0] == 'A')
		{
			out = "1";
		}
		else if(in[0] == 'B')
		{
			out ="2";
		}
		else if(in[0] == 'C')
		{
			out = "3";
		}
		else if(in[0] == 'D')
		{
			out = "4";
		}
		else if(in[0] == 'E')
		{
			out = "5";
		}
		else if (in[0] == 'F')
		{
			out = "6";
		}
		else if (in[0] == 'G')
		{
			out = "7";
		}
		else if(in[0] == 'H')
		{
			out = "8";
		}
		else if(in[0] == 'I')
		{
			out = "9";
		}
		else if(in[0] == 'J')
		{
			out = "10";
		}
		else if(in[0] == 'K')
		{
			out = "11";
		}
		else if(in[0] == 'L')
		{
			out = "12";
		}
		else if(in[0] == 'M')
		{
			out = "13";
		}
		else if(in[0] == 'N')
		{
			out = "14";
		}
		else if(in[0] == 'O')
		{
			out = "15";
		}
		else if(in[0] == 'P')
		{
			out = "16";
		}
		else if(in[0] == 'Q')
		{
			out = "17";
		}
		else if(in[0] == 'R')
		{
			out = "18";
		}
		else if(in[0] == 'S')
		{
			out = "19";
		}
		else if(in[0] == 'T')
		{
			out = "20";
		}
		else if(in[0] == 'U')
		{
			out = "21";
		}
		else if(in[0] == 'V')
		{
			out = "22";
		}
		else if(in[0] == 'W')
		{
			out = "23";
		}
		else if(in[0] == 'X')
		{
			out = "24";
		}
		else if(in[0] == 'Y')
		{
			out = "25";
		}
		else if(in[0] == 'Z')
		{
			out = "26";
		}

		return out;
	}
	int stringtoint(string in)
	{
		int out=atoi(&in[0]);
		return out ;
	}
	void resetVisitedFlags()
	{
		for(int i = 0; i <numofNodes; i++)
		{
			list[i].visited = false;
		}
	}
	bool allvisited()
	{
		for(int i = 0;  i < numofNodes; i++)
		{
			if(list[i].visited == false)
			{
				return false;
			}
		}
		return true;
	}
	int nextinlistUnvisited()
	{
		for(int i = 0; i< numofNodes; i++)
		{
			if(list[i].visited == false)
				return i;
		}
		return -1;
	}
	void printalphadft(int index)
	{
		if(list[index].visited == true)
			return;
		cout<< static_cast<char>(list[index].element+65)<<"    ";
		list[index].visited = true;
		edge * temp= list[index].nextedge;
		for(int i =0; temp != NULL; i++)
		{
			index = temp->to;
			printalphadft(index-1);
			temp = temp->nextedge;
		}
	}
	void printdft(int index)
	{
		if(list[index].visited == true)
			return;
		cout<<list[index].element<<"    ";
		list[index].visited = true;
		edge * temp= list[index].nextedge;
		for(int i =0; temp != NULL; i++)
		{
			index = temp->to;
			printdft(index-1);
			temp = temp->nextedge;
		}
	}
	void topologicalOrdering(int index, stack<int> &topOrder)
	{
		list[index].visited = true;
		edge * temp = list[index].nextedge;
		for(int i = 0; temp!=NULL ; i++)
		{
			if(list[temp->to-1].visited == false)
			{
				topologicalOrdering(temp->to-1, topOrder);
			}
			temp= temp->nextedge;
		}
		topOrder.push(index);	
	}
	
public:
	graph()
	{
		numofNodes=0;
		numofEdges=0;
		list = NULL;
		isletterNodes =false;
	}
	~graph()
	{
		for(int i =0; i<numofNodes; i++)
		{
			edge *temp = list[i].nextedge, *old = list[i].nextedge;
			
			for(int j=0; temp!=NULL; j++)
			{
				temp = temp->nextedge;
				delete old;
				old = temp;
			}
		}
	}
	
	void filein(string filename)
	{
		ifstream ifile(filename);
		if(!ifile)
			return;

		string from, to;
		int weight;
		string s;

		ifile>>numofNodes>>numofEdges;

		list = new graphNode[numofNodes];
		setElements(numofNodes);

		for(int i = 0 ; i<numofEdges; i++)
		{
			ifile>>from>>to>>weight;
			if(isalpha(from[0]))
				isletterNodes =true;
			if(isletterNodes ==true)
			{
				from = toupper(from[0]);
				to = toupper(to[0]);
				from = convertstringalphatostringdigit(from); //if it is letter nodes it converts using ASCI values
				to = convertstringalphatostringdigit(to);// % 64;
			}
			int f =stringtoint(from), t = stringtoint(to);

			edge* temp = list[f-1].nextedge;
			if(temp!=NULL)
			{

				while(temp->nextedge !=NULL)
				{ temp =temp->nextedge;}
				temp->nextedge = new edge;
				temp->nextedge->setEdge(f, t, weight); 
			}
			else
			{
				list[f-1].nextedge = new edge;
				list[f-1].nextedge->setEdge(f, t, weight);
			}
		}
		ifile.close();
	}

	void printList()
	{
		if(isletterNodes)
		{
			for(int i =0; i<numofNodes; i++)
			{
				edge *temp = list[i].nextedge;
				cout<<static_cast<char>(list[i].element+65)<<"    ";
				list[i].visited =true;
				for(int j=0; temp!=NULL; j++)
				{
					temp->printEdge(isletterNodes);
					cout<<"-->";
					temp = temp->nextedge;
				}
				cout<<endl;
			}
		}
		else
		{
			for(int i =0; i<numofNodes; i++)
			{
				edge *temp = list[i].nextedge;
				cout<<list[i].element+1<<"    ";
				for(int j=0; temp!=NULL; j++)
				{
					temp->printEdge();
					cout<<"-->";
					temp = temp->nextedge;
				}
				cout<<endl;
			}
		}
	}
	void printdft()
	{
		cout<<"\nDepth first traversal:\n";
		resetVisitedFlags();
		int index=0;
		if(isletterNodes)
		{
			while(!allvisited())
			{
				index = nextinlistUnvisited();
				cout<< static_cast<char>(list[index].element+65)<<"    ";
				list[index].visited = true;
				edge * temp= list[index].nextedge;
				for(int i =0; temp != NULL; i++)
				{
					index = temp->to;
					printalphadft(index-1);
					temp = temp->nextedge;
				}
			}
		}
		else
		{
			while(!allvisited())
			{
				index = nextinlistUnvisited();
				cout<< list[index].element<<"    ";
				list[index].visited = true;
				edge * temp= list[index].nextedge;
				for(int i =0; temp != NULL; i++)
				{
					index = temp->to;
					printdft(index-1);
					temp = temp->nextedge;
				}
			}
		}
		cout<<"\n\n";
		resetVisitedFlags();
	}
	void TopologicalOrdering()
	{
		stack<int> topOrder;
		resetVisitedFlags();
		while(!allvisited())
		{
			int index = nextinlistUnvisited();
			if (list[index].visited == false)
			{
				topologicalOrdering(index, topOrder);
			}
		}

		stringstream ss;
		if(isletterNodes)
		{
			for(int i =0; i< numofNodes; i++)
			{
				ss << static_cast<char>(topOrder.top()+65)<<"     ";
				topOrder.pop();
			}
		}
		else
		{
			for(int i =0; i< numofNodes; i++)
			{
				ss << topOrder.top()<<"     ";
				topOrder.pop();
			}
		}
		string temp;
		temp = ss.str();
		cout<< "\nTopological Ordering: \n";
		cout<< temp<<endl;
	}


	
 

};

#endif