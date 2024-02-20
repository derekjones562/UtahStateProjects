#include "HashTable.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

void getPoemFromFile(string filename, HashTable<string, vector<WordNode>> &ht);
void makePoemFromHash(string filename, HashTable<string, vector<WordNode>> &ht);
string getBeginWord(string filename, int &length, bool &print);

int main()
{
	string  filename;
	ifstream ifile;
	
	cout <<"\n\n\nEnter file name to create a poem from: ";
	cin >> filename;
	//filename = "Poe.txt";
	ifile.open(filename);
	while(ifile.is_open())
	{
	HashTable<string, vector<WordNode>> dHashTable; //d for derek

	
	getPoemFromFile(filename, dHashTable);
	makePoemFromHash(filename, dHashTable);
	ifile.close();

	cout <<"\n\n\nEnter file name to create a poem from: ";
	cin >> filename;
	ifile.open(filename);
	}
	


	return 0;
}

//read in contents of file and store them correctly in hash table
void getPoemFromFile(string filename, HashTable<string, vector<WordNode>> &ht)
{
	ifstream ifile;
	ifile.open(filename);
	string word, nextWord;
	vector<WordNode> vwn;
	WordNode temp;

	int j=0;
	while(!ifile.eof())
	{
		temp.probability=0;
		
		ifile>>word;
		for (int i = 0; i < word.length();)   
		{

			 if (word[i] >255 || word[i] < 0 || ispunct(word[i]) )  
				 word.erase(i, 1);    
			 else{     
				 word[i] = tolower(word[i]); 
				 i++;    
			 }   
		}
		temp.word = word;
		temp.probability++;
		vwn.push_back(temp);
		if(j!=0)
		{
			ht.insert(vwn.front().word, &vwn);
			vwn.pop_back();
			vwn.pop_back();
			vwn.push_back(temp);
			
		}
		j++;
	}

	ifile.close();

}

void makePoemFromHash(string filename, HashTable<string, vector<WordNode>> &ht)
{
	int length = 20, nWordinPoem, k=0, computingProb=0;
	bool print= false;
	string beginingWord = getBeginWord(filename, length, print);
	if(beginingWord =="file not Found")
		return;
	
	vector<WordNode> temp;
	srand(time(NULL));
	
	for( int i = 0; i< length; i++)
	{
		vector<WordNode> * wnptr = ht.find(beginingWord);
		temp = *wnptr;
		nWordinPoem = rand() % temp[0].probability+1;

		k=1;
		computingProb=temp[k].probability;
		for(int j=1; j != nWordinPoem; j++)
		{
			
			if(computingProb < j )
			{
				k++;
				computingProb += temp[k].probability;
			}
		}
		if(i==0)
			cout<<beginingWord << " ";
		beginingWord = temp[k].word; 
		cout<< beginingWord << " ";
		

	}

	if(print == true)
	{
		cout<<"\n\n\n\n\n\n\n" << ht.toString(30);
	}
	
}

string getBeginWord(string filename, int &length, bool &print)
{
	if(filename == "Seuss.txt")
	{
		length = 50;
		return "mordecai";
	}
	else if(filename == "Poe.txt")
	{
		length = 50;
		return "nevermore";
	}
	else if(filename == "inch.txt")
	{
		length = 50;
		return "computer";
	}
	else if(filename == "clown.txt")
	{
		length = 20;
		return "go";
	}
	else if(filename == "green.txt")
	{
		print = true;
		length = 20;
		return "sam";
	}
	else
	{
		print = true;
		length = 0;
		return "file Not Found";
	}
}