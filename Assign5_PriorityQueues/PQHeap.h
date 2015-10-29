// PQHeap.cpp - wdg 2008
#ifndef PQHeap_H
#define PQHeap_H

#include "PQ.h"

class PQHeap: public PQ 
{
public:
	static const int KIDS = 8; //d-ary heap of 8
	PQHeap(string name, int size);
	void insert(ItemType &);  //    virtual void insert(ItemType & x )=0 ;
	ItemType deleteMax();
	int getCount() const;
	void merge(PQ *h);  // merges h into current heap  
	string toString(int size) const;
private:
	int getBestKid(int bestVal,int curr, int size );
	ItemType * heap;   // Heap Array
	int physicalSize;  // Physical size of heap
};


#endif


