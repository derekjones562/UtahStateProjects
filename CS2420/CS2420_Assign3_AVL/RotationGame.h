#ifndef ROTATION_GAME_H
#define ROTATION_GAME_H

#include <iostream>
#include "BoardClass.h"
#include "avlTree.h"
using namespace std;
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
			gameBoard.move(6);
			gameBoard.move(10);
			gameBoard.history=-1;
			gameBoard.state=0;
			gameBoard.fullHistory="";
			break;
		case 2:
			gameBoard.move(7);
			gameBoard.move(5);
			gameBoard.history=-1;
			gameBoard.state=0;
			gameBoard.fullHistory="";
			break;
		case 3:
			gameBoard.move(1);
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

	void bruteForceSolve()
	{
		gameBoard.solve();
	}
	void aStarSolve()
	{
		int sID=0; //state ID counter. keeps from repeating a state number
		AvlTree<Board> boardt; //AvlTree of Boards

		boardt.insert(gameBoard);
		Board original(gameBoard);//original starting board
		Board compare=boardt.findMin();

		while(sID!= -1)
		{
			for(int i=0; i<12; i++)
			{
				gameBoard = compare;
				sID++; //change state ID counter to 
				gameBoard.state = sID; // give the new board its new state number
				gameBoard.history = compare.state; // give the new board its history number
				gameBoard.fullHistory= gameBoard.move(i);
				cout<<endl;
				gameBoard.print();
				//boardq.push(GameBoard); //add the to the Tree
				if(gameBoard==winning) //check to see if the the move made the winning board 
				{
					cout<<"You WIN!!!\n";
					sID = -1;
					break;
				}
			}
			//boardt.pop();	
		}
		cout<<"Original Board\n";
		original.print();
	}
	int printMenu()
	{
		int option;
		cout<<string(100, '\n');
		cout<<"Input 1:\n564\n829\n173\n\n";
		cout<<"Input 2:\n218\n947\n263\n\n";
		cout<<"Input 3:\nA*Solve\n\n";
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

// State class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void calcExpectd()				   --> stores the underestimated value of the number
//										   of moves it will take to solve the board in expectedCost
// void calcCostSoFar()
// ******************PRIVATE OPERATIONS********************
// 
// ********************************************************
// 
class State
{
public:
	static const int SIZE = 3;
	State()
	{}
	State(Board gb)
	{
		gBoard = gb;
		costSoFar = expectedCost = 0;
	}
	~State()
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
	void calcCostSoFar()
	{
		costSoFar = gBoard.state % 12;
	}
private:
	Board gBoard, winning;
	int costSoFar, expectedCost;
	string fullHistory;
};
#endif