#ifndef LINKEDALLOCATION_H
#define LINKEDALLOCATION_H
#include"HashTable.h"
struct block
{
	short blockid;
	block *nextB;
};
class fNode2 :public fNode
{																								//publically inheritted fnode
public:
	block *Start;
	block *End;																					//data members
	fNode2 *Next;
};

class LinkedList_Allocation:public Hash_Table
{
	fNode2 **htable;
public:
	fNode2* Search(char *str);
	void DisplayDirectory();
	void DeleteFile(char *FEname);

	void Insert(char *fileN, char *Ext, int fsize);
	void Deallocation(char *FEname);
	void display(char *FEname);
	LinkedList_Allocation();
	~LinkedList_Allocation();
	void InitializeTable(int capcty);
	
};
#endif