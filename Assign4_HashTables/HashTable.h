#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
using namespace std;

int nextPrime(int n);
bool isPrime(int n);

enum Status { ACTIVE, EMPTY, DELETED };

struct WordNode
{
public:
	string word;
	int probability; //count
	WordNode()
	{ word= "";
	  probability=0;
	}
	~WordNode(){};
	WordNode& operator=(WordNode rhs)
	{
		this->word = rhs.word;
		this->probability = rhs.probability;
		return *this;
	}
};

// We store two things.  The key itself and the record associated with the key.
// In our case, the HashKey will be a string.  The HashRecord will be a node containing the word, the count, an a vector of succesor information.
template <typename HashKey, typename HashRecord>
class HashEntry
{
public:
	HashKey key;
	HashRecord * rec;
	Status info;

	HashEntry(HashRecord * hr = NULL, const HashKey & e = HashKey(), Status i = EMPTY)
		: key( e ), rec( hr ), info( i )
		{}
	~HashEntry()
	{
		delete rec;
	}


};

template <typename HashKey, typename HashRecord>
class HashTable
{
public:
	bool remove(const HashKey & x);
	bool isEmpty() { return activeElements == 0; }
	HashRecord * insert(const HashKey x, HashRecord * h);
	explicit HashTable(int size = 1973) : hashTable(nextPrime(size))//orginal size = 977 //rehash function doesnt work
	{
		makeEmpty();
	};
	HashRecord *find(const HashKey & x) const;
	void makeEmpty();
	string toString(int howMany = 50);
	

private:
	vector<HashEntry<HashKey, HashRecord>> hashTable;
	int activeElements;
	bool isActive(int currentPos) const;
	size_t myhash(const HashKey & x) const;
	size_t mydoublehash(const HashKey & x) const;
	int findPos(const HashKey & x) const;
	void rehash();
	vector <HashEntry<HashKey, HashRecord>> makeCopyofHashTable(vector<HashEntry<HashKey, HashRecord>> hT);
};

// Convert the Hash table to a string.  Since the hashtablel is large, HowMany indicates how many entries will be displayed.  
template <typename HashKey, typename HashRecord>
string HashTable<HashKey, HashRecord>::toString(int howMany)
{
	int ct = 0;
	stringstream ss;
	ss << "Current size " << hashTable.size() << endl;
	for (int i = 0; i < hashTable.size() && ct < howMany; i++)
		if (hashTable[i].info == ACTIVE){
		     ss << hashTable[i].key << " ";
		     ct++;
		}
	return ss.str();

}

// return the subscript where x is located in the hash table.    
// Quadratic probing is used.  Can you figure out why this implements quadratic probing?
template <typename HashKey, typename HashRecord>
int HashTable<HashKey, HashRecord>::findPos(const HashKey & x) const
{
	int offset = 1;
	//DOUBLE HASHING PART
	int currentPos = myhash(x);

	while (hashTable[currentPos].info != EMPTY &&
		hashTable[currentPos].key != x)
	{
		if(offset == 1) //Double Hash
		{
			currentPos = (mydoublehash(x));
		}
		else
		{
			currentPos = offset;  // Compute ith probe
			
		}
		offset += 5; //linear proble my multiple of 5;
		/*offset += 2;  */ //QUADRATIC PROBING PART


		if (currentPos >= (int)hashTable.size())    // Cheaper than  mod
			currentPos -= hashTable.size(); //wrap  to begining of table
	}

	return currentPos;
};

// Remove all elements of the table by setting status to empty.
// Have you seen the range based loop for accessing elements of a vector?
// for (auto &entry:hashTable) says, let a reference variable "entry" iterate through all entries of the hashTable vector
// The "auto" part says to figure out the type of the element automatically (based on what is passed in).
template <typename HashKey, typename HashRecord>
void HashTable<HashKey, HashRecord>::makeEmpty()
{
	activeElements = 0;
	for (auto & entry : hashTable)
		entry.info = EMPTY;
};

// Create a new hashtable which is at least twice as large as the current size.
// Actually, rehashing can make the table smaller (if entries have been removed), but this isn't considered here.
template <typename HashKey, typename HashRecord>
void HashTable<HashKey, HashRecord>::rehash()
{
	vector<HashEntry <HashKey, HashRecord>> oldhashTable = hashTable;//= makeCopyofHashTable(hashTable);
	

	// Create new double-sized, empty table
	hashTable.resize(nextPrime(2 * oldhashTable.size()));//loses pointer memory and throws off rest of code. dont know how to fix
	for (auto & entry : hashTable)
		entry.info = EMPTY;

	// Copy table over
	activeElements = 0;
	for (auto & entry : oldhashTable)
		if (entry.info == ACTIVE)
			insert(entry.key, entry.rec);
	

	// Copy table over
	
	

};

// Return true if given entry is active.
template <typename HashKey, typename HashRecord>
bool HashTable<HashKey, HashRecord>::isActive(int currentPos) const
{
	return hashTable[currentPos].info == ACTIVE;
};

// use built=in hash functions to find a location.
template<typename HashKey, typename HashRecord>
size_t HashTable<HashKey, HashRecord>::myhash(const HashKey & x) const
{
	static hash<HashKey> hf;
	return hf(x) % hashTable.size();
};

//use built=in hash funtion to find a second location
template<typename HashKey, typename HashRecord>
size_t HashTable<HashKey, HashRecord>::mydoublehash(const HashKey & x) const
{
	static hash<HashKey> hf;
	return (hf(x) + 5)% hashTable.size();
};

// Use lazy deletion to remove an element
// Return boolean to indicate success of operation
template <typename HashKey, typename HashRecord>
bool HashTable<HashKey, HashRecord>::remove(const HashKey & x)
{
	int currentPos = findPos(x);
	if (!isActive(currentPos))
		return false;

	hashTable[currentPos].info = DELETED;
	return true;
};

// Insert item with key x and record pointer h into the hash table.
template<typename HashKey, typename HashRecord>
HashRecord * HashTable<HashKey, HashRecord>::insert(const HashKey x, HashRecord * h)
{
	// Insert x as active
	int currentPos = findPos(x);
	vector<WordNode> temp;
	WordNode move, move2;

	if (isActive(currentPos)) //IF(ALREADY IN HASH TABLE)
	{
		

		while(hashTable[currentPos].rec->size() != 0)
		{
			move = hashTable[currentPos].rec->back();
			temp.push_back(move);
			hashTable[currentPos].rec->pop_back();
		}
		move2 = h->back();
		//next 5 lines puts the first word originally stored back into the vector but with added count(probability)
		temp.back().probability ++;
		move = temp.back();
		hashTable[currentPos].rec->push_back(move);
		temp.pop_back();

		//look through words taken out and put them back if not the current next word. 
		//if current next word is found, add to probability and push_back
		//if not found, add to the end of vector
		//move2 = h->back();
		bool found = false;
		while(temp.empty()!=true)
		{
			move = temp.back();
			
			if(move.word == move2.word)
			{
				move.probability++;
				found =true;
			}
			hashTable[currentPos].rec->push_back(move);
			temp.pop_back();
		}

		if(found == false)
		{
			hashTable[currentPos].rec->push_back(move2);
		}
		
		return h;
	}
	else
	{
		vector<WordNode> *c = new vector<WordNode>; 
		move = h->front();
		c->push_back(move);
		move = h->back();
		c->push_back(move);
		hashTable[currentPos].key = x;
		hashTable[currentPos].rec = c;
		hashTable[currentPos].info = ACTIVE;
	}

	// Rehash; see Section 5.5
	if (++activeElements > (int)(hashTable.size() / 2))
		rehash();

	return h;
};

// Return record for item with key x.
template<typename HashKey, typename HashRecord>
HashRecord * HashTable<HashKey, HashRecord>::find(const HashKey & x) const
{
	int pos = findPos(x);
	if (isActive(pos))
		return hashTable[pos].rec;
	return NULL;
};

// return the copied version of the hashtable. only used in resize() to keep from losing the HashRecords when the
//vector is resized

template<typename HashKey, typename HashRecord>
vector<HashEntry<HashKey, HashRecord>>  HashTable<HashKey, HashRecord>::makeCopyofHashTable(vector<HashEntry<HashKey, HashRecord>> hT)
{
	vector<HashEntry<HashKey, HashRecord>> copyofTable(hT.size());
	HashEntry<HashKey, HashRecord> move;
	for(int i = 0; i < hT.size(); i++)
	{
		move.info = hT[i].info;
		move.key = hT[i].key;
		move.rec = hT[i].rec;
		copyofTable[i] = move;
	}

	return copyofTable;
};
#endif