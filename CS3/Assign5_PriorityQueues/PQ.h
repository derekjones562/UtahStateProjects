#ifndef PQ_H
#define PQ_H
#include "ItemType.h"
#include "Node.h"
#include  <limits>

class PQ
{
  protected:
    string name;  //Name of queue (for documentation purposes)
  public:
	Node * PQheap; //this is the head pointer for the tree used for leftist and skew heaps
	int size;     // Number of actual items in queue.
	PQ(string userDefinedName="No Name") {this->name = userDefinedName; size=0;}
	ItemType deleteMax();
    virtual string toString(int size) const =0;
	int getSize(){return size;}
	bool isEmpty() {return size==0;}
    virtual void insert(ItemType & x )=0 ;
	virtual void merge(PQ * second)=0;
	virtual void makeEmpty() {size=0;}
};
#endif
