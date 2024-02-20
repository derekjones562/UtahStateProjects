#ifndef LeftistHeap_H
#define LeftistHeap_H

#include "PQ.h"

class LeftistHeap: public PQ 
{
public:
	LeftistHeap(string name);
	void insert(ItemType &);  //    virtual void insert(ItemType & x )=0 ;
	Node deleteMax();
	int getCount() const;
	void merge(PQ *second);  // merges h into current heap  
	Node* merge(Node *first, Node *second);
	bool leftistisEmpty();
	string toString() const
	{
		string indent = "  ";
		int s = 5;//s is the size
		return toString(PQheap, indent, s);
	};
	string toString(int size) const;
private:
	ItemType * heap;   // Heap Array
	string toString(Node * ptr, string indent, int &size) const;
	void updateNPL(Node * &head);
	
};


#endif