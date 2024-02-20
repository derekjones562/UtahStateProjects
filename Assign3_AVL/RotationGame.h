#ifndef ROTATION_GAME_H
#define ROTATION_GAME_H

#include <iostream>
#include "BoardClass.h"
#include "avlTree.h"
using namespace std;
// State class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// bool operator< (const Board &rhs) const	-->
// bool operator> (const Board &rhs) const	-->
// void calcExpectd()						--> stores the underestimated value of the number
//												of moves it will take to solve the board in expectedCost
//
// ******************PRIVATE OPERATIONS********************
// string toString() const					-->
// ********************************************************
// 
class GameState
{
public:
	Board gBoard, winning;
	static const int SIZE = 3;
	int costSoFar, expectedCost;

	friend ostream&  operator<<(ostream& ss, const GameState gs);

	bool operator< (const GameState &rhs) const
	{
		if (this->expectedCost == rhs.expectedCost)
			return (this->costSoFar < rhs.costSoFar);
		return (this->expectedCost < rhs.expectedCost);
	} 
	bool operator> (const GameState &rhs) const
	{
		if (this->expectedCost == rhs.expectedCost)
			return (this->costSoFar > rhs.costSoFar);
		return (this->expectedCost > rhs.expectedCost);
	} 
	/*bool operator == (const GameState &rhs) const
	{
		if (this->expectedCost == rhs.expectedCost)
			return (this->costSoFar < rhs.costSoFar);
		else 
			return false;
	}*/
	GameState()
	{
		costSoFar = expectedCost = 0;
	}
	GameState(Board gb)
	{
		gBoard = gb;
		costSoFar = expectedCost = 0;
	}
	~GameState()
	{}
	/**
	* underestimates the number of moves it will take to win
	**/
	void calcExpected()
	{
		int distance = 0; //number of moves needeed for a single digit to make it to its winning column and row
		int rowOfWinning, columnOfWinning, rowOfgBoard, columnOfgBoard;
		int number; //used to store number that we are looking at
		for(int i=0; i<SIZE; i++)
		{
			for(int j=0; j<SIZE; j++)
			{
				rowOfgBoard = i;
				columnOfgBoard = j;
				number = gBoard.board[i][j];
				switch(number)
				{
				case 1:
					rowOfWinning = 0;columnOfWinning = 0;
					break;
				case 2:
					rowOfWinning = 0;columnOfWinning = 1;
					break;
				case 3:
					rowOfWinning = 0;columnOfWinning = 2;
					break;
				case 4:
					rowOfWinning = 1;columnOfWinning = 0;
					break;
				case 5:
					rowOfWinning = 1;columnOfWinning = 1;
					break;
				case 6:
					rowOfWinning = 1;columnOfWinning = 2;
					break;
				case 7:
					rowOfWinning = 2;columnOfWinning = 0;
					break;
				case 8:
					rowOfWinning = 2;columnOfWinning = 1;
					break;
				case 9:
					rowOfWinning = 2;columnOfWinning = 2;
					break;
				} 
				distance += (abs(rowOfgBoard-rowOfWinning))+(abs(columnOfgBoard-columnOfWinning));
			}
		}
		expectedCost=(distance/3)+costSoFar;
	}
private:
	
	
	string toString() const
	{
		stringstream temp;
		temp <<"State " << gBoard.state << "{";
		for(int i = 0; i<SIZE; i++)
		{
			for(int j = 0; j<SIZE; j++)
			{
				temp << gBoard.board[i][j];
			}
			if(i<2)
				temp<< ", ";
			else
				temp<< "} from " <<gBoard.history << " ";
		}
		temp<<gBoard.fullHistory;
		return temp.str();
	}
};
ostream&  operator<<(ostream& ss, const GameState gs) 
{
	ss << gs.toString() << endl;
    return ss;
}
// RotationGame class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// int solve ()				  --> calls printMenu() then calls the proper solve function 
//								  based on option selected in printmenu(). returns option
//								  selected in printMenu
// void setBoard( int )		  --> used in printMenu() to set the board according to option
// 
// ******************PRIVATE OPERATIONS********************
// void bruteForceSolve       --> solve the game using the brute force method. This 
//								  is where boards are stored in a Queue and Every
//								  posible move is tried until the solution is found
// void aStarSolve            --> 
// int printMenu()			  --> prints options menu. gets then returns the option selected
// void resetBoard()		  --> set gameBoard back to the winning Board
// 
// ********************************************************
// 
class RotationGame
{
public:
	RotationGame()
	{}
	~RotationGame()
	{}
	/**
	*returns option chosen in printMenu
	**/
	int solve ()
	{
		int option = printMenu();
		switch(option)
		{
		case 1:
		case 2:
			bruteForceSolve();
			break;
		case 3:
		case 4:
			aStarSolve();
			break;
		default:
			break;
		}
		resetBoard(); //after solving, reset the board
		return option;
	}
	
	
	void setBoard(int option)
	{
		int num; 

		switch(option)//sets GameBoard to appropriate board
		{
		case 1:
			gameBoard.board[0][0] = 5;
			gameBoard.board[0][1] = 6;
			gameBoard.board[0][2] = 4;
			gameBoard.board[1][0] = 8;
			gameBoard.board[1][1] = 2;
			gameBoard.board[1][2] = 9;
			gameBoard.board[2][0] = 1;
			gameBoard.board[2][1] = 7;
			gameBoard.board[2][2] = 3;
			gameBoard.history=-1;
			gameBoard.state=0;
			gameBoard.fullHistory="";
			break;
		case 2:
			gameBoard.board[0][0] = 2;
			gameBoard.board[0][1] = 1;
			gameBoard.board[0][2] = 8;
			gameBoard.board[1][0] = 9;
			gameBoard.board[1][1] = 4;
			gameBoard.board[1][2] = 7;
			gameBoard.board[2][0] = 3;
			gameBoard.board[2][1] = 6;
			gameBoard.board[2][2] = 5;
			gameBoard.history=-1;
			gameBoard.state=0;
			gameBoard.fullHistory="";
			break;
		case 3:
			
			gameBoard.board[0][0] = 5;
			gameBoard.board[0][1] = 6;
			gameBoard.board[0][2] = 4;
			gameBoard.board[1][0] = 8;
			gameBoard.board[1][1] = 2;
			gameBoard.board[1][2] = 9;
			gameBoard.board[2][0] = 1;
			gameBoard.board[2][1] = 7;
			gameBoard.board[2][2] = 3;
			gameBoard.history=-1;
			gameBoard.state=0;
			gameBoard.fullHistory="";
			gameBoard.print();
			break;
		case 4:
			gameBoard = winning; // this is to reset GameBoard to a winning board 
								//ready to be jumbled rather than jumbling a jumbled board
			do
			{cout<<"Enter number of times to be jumbled: ";
			cin>>num;
			}while(num<0||num>500);
			gameBoard.jumble(num);
			break;
		case 0:
			break;
		}
	}
private:
	Board winning;
	Board gameBoard;
	GameState gameB;

	void bruteForceSolve()
	{
		gameBoard.solve();
	}
	void aStarSolve()
	{
		int sID=0; //state ID counter. keeps from repeating a state number
		int costSoFarCounter=0, removecount=0;
		AvlTree<GameState> boardt;//AvlTree of GameBoards sorted by Gamestate

		boardt.insert(gameBoard);
		GameState original(gameBoard);//original starting board
		GameState compare; //best priority will be the minimum cost which should be te min value
		while(sID!= -1)
		{
			costSoFarCounter++;
			compare=boardt.findMin();//change compare to the best priority

			for(int i=0; i<12; i++)
			{
				gameB = compare.gBoard;
				sID++; //change state ID counter to 
				gameB.gBoard.state = sID; // give the new board its new state number
				gameB.gBoard.history = compare.gBoard.state; // give the new board its history number
				gameB.gBoard.fullHistory= gameB.gBoard.move(i);
				gameB.costSoFar = costSoFarCounter;
				gameB.calcExpected();
				//cout<<endl;
				//gameB.print();
				boardt.insert(gameB); //add the to the Tree
				if(gameB.gBoard==winning) //check to see if the the move made the winning board 
				{
					cout << "State "<<gameB.gBoard.state<<" From "<<gameB.gBoard.history <<gameB.gBoard.fullHistory<< endl;
					
					cout<<"You WIN!!!\n";
					sID = -1;
					break;
				}
			}
			cout <<"Removed: "<< compare << endl;
			boardt.removeMin();	
			removecount++;
		}
		cout<<"Original Board\n";
		cout << original;
		cout<<"RemoveCount = " << removecount << endl;
	}
	int printMenu()
	{
		int option;
		cout<<string(10, '\n');
		cout<<"Input 1:\n564\n829\n173\n\n";
		cout<<"Input 2:\n218\n947\n365\n\n";
		cout<<"Input 3:\nA*Solve: Input 1\n\n";
		cout<<"Input 4:\nCreate jumbled board\n\n";
		cout<<"Input 0:\nExit\n\n";
		cout<<"Enter Input number you want solved: ";
		cin>>option;
		if(option<0 || option>4)
			cout<<"Please enter a correct input";
		setBoard(option);
		return option;
	}
	void resetBoard()
	{
		gameBoard = winning;
	}
};


#endif