#include "graph.h"
#include<string>

using namespace std;

int main()
{
	string filename = "prog7A.txt";
	graph test;
	test.filein(filename);
	test.printList();
	test.printdft();
	test.TopologicalOrdering();

	return 0;
}