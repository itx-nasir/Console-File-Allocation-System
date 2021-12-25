#ifndef INDEXEDALLOCATION_H
#define INDEXEDALLOCATION_H
#include"HashTable.h"

class fNode3 :public fNode
{
public:
	short *IndexBlock;
	
	fNode3 *Next;
};

class Indexed_Allocation :public Hash_Table
{
	fNode3 **htable;
public:
	fNode3* Search(char *str);
	void Allocation(fNode3 *&);
	void Insert(char *fileN, char *Ext, int fsize);
	void Deallocation(char *FEname);
	void display(char *FEname);

	void DisplayDirectory();
	void DeleteFile(char *FEname);

	Indexed_Allocation();
	~Indexed_Allocation();
	void InitializeTable(int capcty);

};
#endif