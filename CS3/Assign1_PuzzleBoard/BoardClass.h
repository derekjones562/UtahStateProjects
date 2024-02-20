#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <sstream>
using namespace std;


class Board {
public:
	static const int SIZE = 3;
	int history; //keeps track of which state this board came from
	int state;  //number of moves made from original board
	int board[SIZE][SIZE];  // Values of board
	string fullHistory;// keeps track of moves from initial board to winning board

	Board(const Board & b);  //Create board from another board
	Board(int[][SIZE]); //create board form 2d array
	string move(int m);  //m is which move.  s is the current state. Returns string describing move 
	void makeBoard(int jumbleCt = 0);  //Starting from a perfect board, do jumbleCt moves to alter it
	string toString();  //return a string which represents the contents of the board
	bool operator==(Board &b);   //Return true if two boards are equal
	Board(); //inializes history and state and sets board to all 0's
	void rotateEast(int row);
	void rotateWest(int row);
	void rotateNorth(int col);
	void rotateSouth(int col);
	void jumble(int ct);  //Do jumble moves to alter board
	void print(); //prints board to the screen
	bool ifile(string fname); //opens a file and fills board with values from file, returns true if worked
	void solve();
	
};


class Q //queue specifically for boards
{
private:
public:
	struct node
	{
		Board b;
		node* next;
		node(){next = NULL;}
	};
	node *begin;
	node *end;
	Q();
	~Q();
	Board pop();
	void push(Board);
	//Board find(int state);// returns the board of the state that is passed... possible not needed for this assignment
	bool isempty();


};
//**************************************************************************
//                          Board Class functions
//***************************************************************************

// Create a printable representation of the Board class
// The stringstream allows you to use the power of output commands in creating a string
string Board::toString() {
	stringstream ss;
	for (int i=0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			ss << board[i][j] << " ";
		ss << endl;
	}
	return ss.str();
};

// return true if board is identical to b
bool Board::operator==(Board &b) {

	for (int i=0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] != b.board[i][j]) return false;
	return true;
}

//Create a board by performing legal moves on a board
//jumbleCt indicates the number of moves that may be required
//if jumbleCt ==0, return the winning board
void Board::makeBoard(int jumbleCt) {
	int val=1;
	for (int i=0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = val++;
	jumble(jumbleCt);
	history=-1;
	state=0;
}

//inializes history and state and sets board to winning board
Board::Board() {
	makeBoard();
}
//Copy constructor
Board::Board(const Board & b) {
	for (int i=0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = b.board[i][j];
	state = b.state;
	history = b.history;
	fullHistory = b.fullHistory;
}
//another constructor
Board::Board(int b[][SIZE])
{
	for (int i=0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = b[i][j];
	state = 0;
	history = -1;
	fullHistory = "";
}


//Rotate East using row specified
void Board::rotateEast(int row){
	if (row <0|| row >=SIZE) return;
	int wrap = board[row][SIZE-1];
	for (int i = SIZE-2; i >=0; i--)
		board[row][i+1] = board[row][i];
	board[row][0] = wrap;
}
//Rotate West using row specified
void Board::rotateWest(int row){
	if (row <0 || row >=SIZE) return;
	int wrap = board[row][0];
	for (int i = 0; i <SIZE-1; i++)
		board[row][i] = board[row][i+1];
	board[row][SIZE-1] = wrap;
}

//Rotate South using column specified
void Board::rotateSouth(int col){
	if (col <0||col >=SIZE) return;
	int wrap = board[SIZE-1][col];
	for (int i = SIZE-2; i >=0; i--)
		board[i+1][col] = board[i][col];
	board[0][col] = wrap;
}
//Rotate North using column specified
void Board::rotateNorth(int col){
	if (col <0||col >=SIZE) return;
	int wrap = board[0][col];
	for (int i = 0; i <SIZE-1; i++)
		board[i][col] = board[i+1][col];
	board[SIZE-1][col] = wrap;
}

// Randomly apply ct moves to the board
void Board::jumble(int ct) {
	for (int i=0; i < ct; i++)
		move(rand()%(SIZE*4));
}


// Make one move.  m indicates which move is wanted. Return string describing the move. 
// s is the current state that is move will make. ie if 3 is passed, this move will make the 3rd state
string Board::move(int m){
	stringstream ss;
	int sub = m/ 4;
	switch (m%4)
	{
	case 0:  rotateNorth(sub); ss << fullHistory << "=>North Col" << sub; break;
	case 1:  rotateSouth(sub); ss << fullHistory <<"=>South Col" << sub; break;
	case 2:  rotateEast(sub); ss << fullHistory <<"=>East Row" << sub; break;
	case 3:  rotateWest(sub); ss << fullHistory <<"=>West Row" << sub; break;
	}

	return ss.str();
}

//prints out board in a 3x3 matix
void Board::print()
{
	cout<<"State "<<state<<" From State "<<history<<" "<<fullHistory<<endl;
	for(int i = 0; i <SIZE; i++)
	{
		for(int j = 0; j <SIZE; j++)
		{
			cout<<board[i][j]<<' ';
		}
		cout<<endl;
	}
}

//
bool Board::ifile(string fname)
{
	ifstream f(fname,ios::in);
	if(f)
	{
		for(int i=0; i< SIZE; i++)
		{
			for(int j=0; j < SIZE; j++)
			{
				f >> board[i][j];
			}
		}
		f.close();

		return true;
	}
	else
	{
		cout<<"Error opening file\n";
		return false;
	}
}

void Board::solve()
{
	int sID=0; //state ID counter. keeps from repeating a state number
	Board WB;	//create the "winning board" to compare to
	Q boardq; //Queue of Boards
	Board GameBoard;
	GameBoard = board;
	int popCounter=0,pushCounter=0;

	boardq.push(GameBoard);
	pushCounter++;
	Board Original(GameBoard);//original starting board

		while(sID!= -1)
	{
		for(int i=0; i<12; i++)// do for each move in this case there are 12 possible
		{
			GameBoard = boardq.begin->b;
			sID++; //change state ID counter to 
			GameBoard.state = sID; // give the new board its new state number			
			GameBoard.history = boardq.begin->b.state; // give the new board its history number
			GameBoard.fullHistory= GameBoard.move(i);
			cout<<endl;
			GameBoard.print();
			boardq.push(GameBoard); //add the new board to the queue
			if(GameBoard==WB) //check to see if the the move made the winning board 
			{
				cout<<"You WIN!!!\n";
				sID = -1;
				break;
			}
		}
		boardq.pop();
		popCounter++;
	}
	cout<<"Original Board\n";
	Original.print();
}

//***************************************************************************
//                          Q class funcions
//****************************************************************************

Q::Q()
{
	begin = NULL;
	end = NULL;
}

Q::~Q()
{
	node *ptr, *next;
	ptr = begin;
	while(ptr != NULL)
	{
		next = ptr->next;
		delete ptr;
		ptr = next;
	}
}

//"pops" the begining board off of the queue and stores it in the board passed
Board Q::pop()
{
	Board gboard;
	node *ptr;
	if(!isempty())
	{
		gboard = begin->b;
		ptr = begin->next;
		delete begin;
		begin=ptr;
		if (begin==NULL)
			end = NULL;
	}
	return gboard;
}

//"pushes" the board passed onto the end of the queue
void Q::push(Board gboard)
{
	node *ptr;
	ptr = new node;
	ptr->b = gboard;
	if(isempty())
	{
		end = ptr;
		begin = ptr;
		ptr->next = NULL;
	}
	else
	{
		ptr->next = NULL;
		end->next = ptr;
		end = ptr;
	}
}

/*Board Q::find(int state)
{
	return b;
}*/

bool Q::isempty()
{
	bool answer = false;
	if(end==NULL)
		answer = true;
	return answer;
}
#endif