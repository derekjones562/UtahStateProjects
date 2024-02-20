#include "BoardClass.h"

int main()
{
	int option, num;
	Board GameBoard, starting;
	
	do
	{
		cout<<string(100, '\n');
		cout<<"Input 1:\n123\n645\n978\n\n";
		cout<<"Input 2:\n183\n524\n769\n\n";
		cout<<"Input 3:\n672\n159\n348\n\n";
		cout<<"Input 4:\nCreate jumbled board\n\n";
		cout<<"Input 0:\nExit\n\n";
		cout<<"Enter Input number you want solved: ";
		cin>>option;
		if(option<0 || option>4)
			cout<<"Please enter a correct input";

		switch(option)//sets GameBoard to appropriate board
		{
		case 1:
			GameBoard.move(6);
			GameBoard.move(10);
			GameBoard.history=-1;
			GameBoard.state=0;
			GameBoard.fullHistory="";
			break;
		case 2:
			GameBoard.move(7);
			GameBoard.move(5);
			GameBoard.history=-1;
			GameBoard.state=0;
			GameBoard.fullHistory="";
			break;
		case 3:
			GameBoard.move(1);
			GameBoard.move(8);
			GameBoard.move(2);
			GameBoard.move(10);
			GameBoard.history=-1;
			GameBoard.state=0;
			GameBoard.fullHistory="";
			GameBoard.print();
			break;
		case 4:
			GameBoard=starting; // this is to reset GameBoard to a winning board 
								//ready to be jumbled rather than jumbling a jumbled board
			do
			{cout<<"Enter number of times to be jumbled: ";
			cin>>num;
			}while(num<0||num>500);
			GameBoard.jumble(num);
			break;
		case 0:
			break;
		}
		if(option!=0)
			GameBoard.solve();
	}while(option != 0);
	
	//GameBoard.ifile("test.txt");//create gameboard with test numbers. with format:
	//1' '2' '3 
	//4' '5' '6
	//7' '8' '9
										
	//GameBoard.solve();


	return 0;
}