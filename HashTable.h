#ifndef HASH_TABLE_H
#define HASH_TABLE_H

class fNode
{																		//node class
public:
	char File[25];
	char Extn[5];														//data members
	int fsize;
};

class Hash_Table
{  protected:
	
	int capacity;
	int size;															//data members for class Hash_table
	char Disk[64];
	int nfillblocks;
	
public:
	void SplitString(char *str, char *F, char *E);

	int Hash_Function(char *);
	void copystr(char *f7, char *p);
	void combineStrings(char *F, char *E, char *t);
	void DisplayDisk();
	int getSize()
	{
		return size;
	}
	int getFreeSpace()
	{
		return (64 - nfillblocks);
	}
};

#endif