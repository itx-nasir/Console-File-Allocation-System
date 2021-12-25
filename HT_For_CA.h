#ifndef HT_For_CA_H
#define HT_For_CA_H
#include"HashTable.h"



class fNode1 :public fNode
{																//inherited Fnode class
public:	
																								
	int start;													//data members														
	fNode1 *Next;

};


class HT_For_CA : public Hash_Table
{

	fNode1 **htable;
public:
	
	void DisplayDirectory();
	void display(char *FEname);
	fNode1* Search(char *str);
	HT_For_CA();
	~HT_For_CA();
	void Deallocation(char *FEname);
	void DeleteFile(char *FEname);
	int DiskAllocation(int st, int siz);
	void InitializeTable(int capcty);
	void Insert(char *fileN, char *Ext, int fsize);
	
};
#endif