#ifndef SkewHeap_H
#define SkewHeap_H

#include "PQ.h"

class SkewHeap: public PQ 
{
public:
	SkewHeap(string name);
	void insert(ItemType &);  //    virtual void insert(ItemType & x )=0 ;
	Node deleteMax();
	int getCount() const;
	void merge(PQ *second);  // merges second into current heap  
	Node* merge(Node *first, Node *second);
	bool SkewisEmpty();
	string toString() const
	{
		string indent = "  ";
		int s = 5;
		return toString(PQheap, indent, s);
	};
	string toString(int size) const;
private:
	ItemType * heap;   // Heap Array
	string toString(Node * ptr, string indent, int &size) const;
	void updateNPL(Node * &head);
};


#endif