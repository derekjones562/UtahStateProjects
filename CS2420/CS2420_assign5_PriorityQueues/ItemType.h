#ifndef ITEMTYPE_H
#define ITEMTYPE_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <assert.h>
using namespace std;

class ItemType
{ public:
   string word;            // word
   int priority;           // Priority of ItemType   
   ItemType(string aword = "", int p=0) { word = aword;  priority = p;}
   string toString() { 
       stringstream out;
       out << word  << ":" <<  priority;
       return out.str();
    }
};
#endif