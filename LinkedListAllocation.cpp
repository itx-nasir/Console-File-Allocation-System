#include"LinkedAllocation.h"
#include<iostream>
using namespace std;

LinkedList_Allocation::LinkedList_Allocation()
{
	capacity = 0;
	size = 0;
	for (int i = 0; i < 64; i++)				//constructor
	{
		Disk[i] = 'E';                        //E for empty block
	}
}

void LinkedList_Allocation::InitializeTable(int capcty)
{
	capacity = capcty;
	htable = new fNode2 *[capacity];
	for (int i = 0; i < capacity; i++)						//parameterized constructor
	{
		htable[i] = NULL;
	}
}


void LinkedList_Allocation::Insert(char *fileN, char *Ext, int fsiz)
{
	fNode2 *temp = new fNode2;
	copystr(temp->File, fileN);
	copystr(temp->Extn, Ext);
	temp->Start = NULL;
	temp->End = NULL;
	temp->fsize = fsiz;
	temp->Next = NULL;
    int index = Hash_Function(fileN);
	
	short r;


	if ((64 - nfillblocks)<temp->fsize)
	{
		cout << "\n\nNo Enough Free Space Available \n";
	}
	else
	{
		for (int i = 1; i <= temp->fsize; i++)
		{
			block *tmp = new block;
			
			while (1)
			{

				r = rand() % 64;
				if (Disk[r] == 'E')
				{
					tmp-> blockid= r;
					tmp->nextB = NULL;
					if (temp->Start == NULL)
					{
						temp->Start = tmp;
					}
					else
					{
						block *cur1 = temp->Start;
						while (cur1->nextB != NULL)												//function for allocation of space in hash table
						{
							cur1 = cur1->nextB;
						}
						cur1->nextB = tmp;
					}

					Disk[r] = 'O';
					break;
				}
			}
		}
		cout << "ALlcocted Successfully.\n";
	}

	if (htable[index] == NULL)
	{
		htable[index] = temp;

	}
	else
	{
		fNode2 *cur = htable[index];
		while (cur->Next != NULL)
		{
			cur = cur->Next;
		}
		cur->Next = temp;
	}
	
	size++;
	nfillblocks += fsiz;
}




fNode2* LinkedList_Allocation::Search(char *str)
{

	char F[25]; char E[5];
	SplitString(str, F, E);
	int index = Hash_Function(F);
	
	fNode2 *cur = htable[index];
	
	while (cur != NULL)
	{
		if (strcmp(F, cur->File) == 0 && strcmp(E, cur->Extn) == 0)			//searching the file in the hash table
		{
			return cur;
		}
		cur = cur->Next;
	}
	return cur;


}


void LinkedList_Allocation:: Deallocation(char *FEname)
{
	
	fNode2 *cur = Search(FEname);
		if (cur!=NULL)
		{
			if (cur->Start != NULL)
			{
				block *temp;
				block *current = cur->Start;
				while (current)
				{
					Disk[current->blockid] = 'E';	
					current->blockid = -1;						//deallocation of allocated blocks of a file
					temp = current;
					current = current->nextB;
					delete temp;
				}

				cur->Start = NULL;
				cout << "\nAllocated block for File Deleted Successfully \n" << FEname<<endl;
			}
			else
			{
				cout << "No allocated blocks for the file " << FEname<<endl;
			}
		}

		else
		{
			cout << "\nDeletion Unsuccessful\n\nThe file is not in the director"<<FEname<<endl;
		}
}
	



void LinkedList_Allocation:: display(char *FEname)
{
	fNode2 *cur = Search(FEname);
	if (cur == NULL)
	{
		cout << "\n\nNo File Found\n";
	}
	else
	{
		cout << "File Name with Extention : " << cur->File << "." << cur->Extn << endl;
		cout << "File size " << cur->fsize << endl;
		
		block *current = cur->Start;								//printing or displaying of file name with extensions
				if (current)
				{
					cout << "Allocated Blocks are.\n";
				}
				else
				{
					cout << "No allocated bolcks.\n";
				}
			while (current)
			{
				cout << current->blockid << "    ";
				current = current->nextB;

			}
			
		
	}
	
}

void LinkedList_Allocation::DeleteFile(char *FEname)
{
	Deallocation(FEname);
	char F[25]; char E[5];
	SplitString(FEname, F, E);
	int index = Hash_Function(F);
	fNode2 *cur = htable[index];
	fNode2 *temp;
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
LinkedList_Allocation::~LinkedList_Allocation()
{
	for (int i = 0; i < capacity; i++)
	{
		
		fNode2 *temp2;
		fNode2 *cur = htable[i];
		while (cur != NULL)
		{
			char temp[30];
			combineStrings(cur->File, cur->Extn, temp);
			Deallocation(temp);
			 temp2 = cur;											//deletion or deallocation oh hashtable
			 htable[i] = cur->Next;
			cur = htable[i];
			delete temp2;
			
		}
		htable[i] = NULL;
	}
	delete [] htable;
	cout << "Hash table is cleared.\n";
}




void LinkedList_Allocation::DisplayDirectory()
{
	if (size != 0)
	{
		int j = 1;
		cout << "\t\t\t***FILES IN THE DIRECTORY ARE***\n\n";
		for (int i = 0; i < capacity; i++)
		{


			fNode2 *cur = htable[i];
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