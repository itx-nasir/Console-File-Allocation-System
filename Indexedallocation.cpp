#include"IndexedAllocation.h"

#include<iostream>
using namespace std;

Indexed_Allocation::Indexed_Allocation()
{
	capacity = 0;
	size = 0;
	for (int i = 0; i < 64; i++)
	{
		Disk[i] = 'E';                        //E for empty block
	}
}

void Indexed_Allocation::InitializeTable(int capcty)
{
	capacity = capcty;
	htable = new fNode3 *[capacity];
	for (int i = 0; i < capacity; i++)													//initializing same as default constructor
	{
		htable[i] = NULL;
	}
}


void Indexed_Allocation::Insert(char *fileN, char *Ext, int fsiz)
{
	fNode3 *temp = new fNode3;
	copystr(temp->File, fileN);
	copystr(temp->Extn, Ext);
	temp->fsize = fsiz;
	temp->IndexBlock = NULL;
	temp->Next = NULL;
	int index = Hash_Function(fileN);
	
	Allocation(temp);
	
	if (htable[index] == NULL)
	{
		htable[index] = temp;													//insertion or allocation of a new node

	}
	else
	{
		fNode3 *cur = htable[index];
		while (cur->Next != NULL)
		{
			cur = cur->Next;
		}
		cur->Next = temp;
	}


	size++;
	nfillblocks += fsiz;
}


void Indexed_Allocation:: Allocation(fNode3 *&cur)
{
	
	if ((64 - nfillblocks)<cur->fsize)
	{
		cout << "\n\nNo Enough Free Space Available \n";
	}
	else
	{
		
		cur->IndexBlock = new short[cur->fsize];
		int r=nfillblocks;

		
		for (short i = 0; i < cur->fsize; i++)
		{
			while (1)
			{
																		//allocation into the free space available
				
				if (Disk[r] == 'E')
				{
					Disk[r] = 'O';
					cur->IndexBlock[i] = r;
					
					break;
				}
				r = (r % 63) + 1;
			}
		}
		cout << "Allcocted Successfully.\n";
	}

	
}

fNode3* Indexed_Allocation::Search(char *str)
{

	char F[25]; char E[5];
	SplitString(str, F, E);																				//splitig up the file name and extension
	int index = Hash_Function(F);

	fNode3 *cur = htable[index];

	while (cur != NULL)
	{
		if (strcmp(F, cur->File) == 0 && strcmp(E, cur->Extn) == 0)										//comapring it with the already present substrings in the hash table
		{
			return cur;
		}
		cur = cur->Next;
	}
	return cur;


}


void Indexed_Allocation::Deallocation(char *FEname)
{

	fNode3 *cur = Search(FEname);
	if (cur == NULL)
	{
		cout << "\nDeletion Unsuccessful\n\nThe file is not in the directory" << FEname << endl;
		return;																											//if the file is not the directory
	}
	
	if (cur->IndexBlock == NULL)
	{
		cout << "No allocated blocks for the file " << FEname << endl;													//the files are present but are empty 
		return;
	}																				
	for (short i = 0; i < cur->fsize; i++)
	{
		Disk[cur->IndexBlock[i]]='E';
	}
	delete [] cur->IndexBlock;

	cur->IndexBlock = NULL;
	nfillblocks -= cur->fsize;
	cout << "\nAllocated block for File Deleted Successfully \n" << FEname << endl;									//deletion of the allocated block
	DeleteFile(FEname);
	
}



void Indexed_Allocation::display(char *FEname)
{
	fNode3 *cur = Search(FEname);
	if (cur == NULL)
	{
		cout << "\n\nNo File Found in directory with name " << FEname << endl;
	}
	else
	{
		cout << "File Name with Extention : " << cur->File << "." << cur->Extn << endl;
		cout << "File size " << cur->fsize << endl;

		
		if (cur->IndexBlock)
		{
			cout << "Allocated Blocks are.\n";							//only displaying the file names and extensions if present
		}
		else
		{
			cout << "No allocated bolcks.\n";							//flag raised if there is no such allocated block
		}
		short j = 0;
		while (j<cur->fsize)
		{
			cout << cur->IndexBlock[j]<< "    ";
			j++;

		}


	}

}
Indexed_Allocation::~Indexed_Allocation()
{
	for (int i = 0; i < capacity; i++)
	{

		fNode3 *temp2;
		fNode3 *cur = htable[i];
		while (cur != NULL)
		{
			char temp[30];
			combineStrings(cur->File, cur->Extn, temp);													//destructor
			Deallocation(temp);
			temp2 = cur;
			htable[i] = cur->Next;
			cur = htable[i];
			delete temp2;

		}
		htable[i] = NULL;
	}
	delete[] htable;
	cout << "Hash table is cleared.\n";
}

void Indexed_Allocation::DeleteFile(char *FEname)
{
	Deallocation(FEname);
	char F[25]; char E[5];
	SplitString(FEname, F, E);
	int index = Hash_Function(F);
	fNode3 *cur = htable[index];
	fNode3 *temp;
	if (Search(FEname))
	{
		if (cur->Next == NULL)
		{
			htable[index] = htable[index]->Next;
		}
		else
		{
			bool found = 0;
			while (cur->Next != NULL && !found)
			{
				if (strcmp(F, cur->File) == 0 && strcmp(E, cur->Extn) == 0)
				{
					found = 1;
				}
				else
				{
					temp = cur;
					cur = cur->Next;
				}
			}
			temp->Next = cur->Next;
			delete cur;
		}
	}
	size--;
}

void Indexed_Allocation::DisplayDirectory()
{
	if (size != 0)
	{
		int j = 1;
		cout << "\t\t\t***FILES IN THE DIRECTORY ARE***\n\n";
		for (int i = 0; i < capacity; i++)
		{


			fNode3 *cur = htable[i];
			while (cur != NULL)
			{
				cout << "\t\t\tFILE " << j << " DETAILS ARE \n" << endl;
				char str[30];
				combineStrings(cur->File, cur->Extn, str);
				display(str);
				cur = cur->Next;
				j++;
			}

		}
	}
	else
	{
		cout << "Your Hash Table is empty.\n";
	}
}