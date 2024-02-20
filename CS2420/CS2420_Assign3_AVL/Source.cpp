
#include "avlTree.h"
#include "RotationGame.h"
#include "BoardClass.h"
#include <vector>

using namespace std;

void AvlIntTreeFunction();
void RotationGameFunction();

int main()
{
	//AvlIntTreeFunction();

	//RotationGameFunction();
	State test;
	
	test.calcExpected();
	
	return 0;
}

void AvlIntTreeFunction()
{
	AvlTree<int> numbers;
	numbers.insert(1);
	numbers.insert(3);
	numbers.insert(5);
	numbers.insert(7);
	numbers.insert(9);
	numbers.insert(11);
	numbers.insert(2);
	numbers.insert(4);
	numbers.insert(8);
	
	cout<< "Starting <int> tree\n";
	cout << numbers.toString();

	numbers.remove(7);
	numbers.remove(9);

	cout<< "Remove 7 and 9\n";
	cout <<endl << numbers.toString() << endl;

	numbers.insert(50);
	numbers.insert(30);
	numbers.insert(15);
	numbers.insert(18);

	cout << "Insert 50, 30, 15, and 18\n";
	cout << endl << numbers.toString() << endl;

	numbers.removeMin();
	numbers.removeMin();
	numbers.removeMin();

	cout << "Remove the 3 lowest or minimum values\n";
	cout << endl << numbers.toString() << endl;
	
	numbers.insert(17);

	cout << "Insert 17\n";
	cout << endl << numbers.toString() << endl;
}
void RotationGameFunction()
{
	RotationGame gameBoard;
		
	while( gameBoard.solve() != 0)
	{}
		
}