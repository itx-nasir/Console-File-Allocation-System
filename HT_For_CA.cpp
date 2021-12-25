#include"HT_For_CA.h"
#include<iostream>
#include<cstring>
using namespace std;
HT_For_CA::HT_For_CA()
{

	capacity = 0;
	size = 0;
	for (int i = 0; i < 64; i++)
	{
		Disk[i] = 'E';                        //E for empty block
	}
}


fNode1* HT_For_CA::Search(char *str)
{

	char F[25]; char E[5];
	SplitString(str, F, E);
	int index = Hash_Function(F);
	
	fNode1 *cur = htable[index];
																	//Function to search in the substrings that have been split 
	while (cur != NULL)
	{
		if (strcmp(F, cur->File) == 0 && strcmp(E, cur->Extn) == 0)
		{
			return cur;
		}
		cur = cur->Next;
	}
	return cur;


}

void HT_For_CA::InitializeTable(int capcty)
{
	capacity = capcty;
	htable = new fNode1 *[capacity];
	for (int i = 0; i < capacity; i++)								//initializing hash table here
	{
		htable[i] = NULL;
	}
}

int HT_For_CA::DiskAllocation(int st, int siz)
{
	int count = 0;
	if ((siz) >(64 - nfillblocks))
	{
		return -1;
	}
	else
	{
		for (int k = st; k<(st + siz); k++)
		{
			if (Disk[k] == 'E')
			{
				count++;											//Function for allocation of disk													
			}
		}
		if (siz == count)
		{
			for (int j = st; j < (st + siz); j++)
			{
				Disk[j] = 'O';

			}
			return 1;
		}


	}
	return 0;
}

void HT_For_CA::Insert(char *fileN, char *Ext, int fsiz)
{
	fNode1 *temp = new fNode1;
	copystr(temp->File, fileN);
	copystr(temp->Extn, Ext);
	temp->start = nfillblocks;
	temp->fsize = fsiz;
	temp->Next = NULL;
	int index = Hash_Function(fileN);
	fNode1 *cur = htable[index];
	if (htable[index] == NULL)
	{
		htable[index] = temp;

	}
	
	else
	{
		
		while (cur->Next != NULL)
		{															//Function for space allocation
			cur = cur->Next;
		}
		cur->Next = temp;
	}
	int isAllocate = DiskAllocation(temp->start, temp->fsize);
	if (isAllocate == -1)
	{
		cout << "Not allocated because,Availble space is less than required space\n";
		cur->Next->start = -1;
	}
	else if (isAllocate == 0)
	{
		cur->Next->start = -1;
		cout << "Not allocated because contigous available blocks are less than required blocks\n";
	}
	else
	{
		cout << "Space allocated succefully.\n";
	}
	size++;
	nfillblocks += fsiz;
}
void HT_For_CA::Deallocation(char *FEname)
{
	fNode1 *cur = Search(FEname);
	for (int i = cur->start; i < cur->fsize; i++)
	{
		Disk[i] = 'E';
	}
	cur->start = -1;
	nfillblocks -= cur->fsize;
}
void HT_For_CA::DeleteFile(char *FEname)
{
	Deallocation(FEname);
	char F[25]; char E[5];
	SplitString( FEname,F,E);
	int index = Hash_Function(F);
	fNode1 *cur = htable[index];
	fNode1 *temp;
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

void HT_For_CA::display(char *FEname)
{
	fNode1 *cur = Search(FEname);
	if (cur == NULL)
	{
		cout << "\n\nNo File Found in directory with name " << FEname << endl;
	}
	else
	{
		
		cout << "Name                 Size               Start \n";
		cout << cur->File << "." << cur->Extn << "                 " << cur->fsize <<"           "<< cur->start << endl;
		


		if (cur->start!=-1)
		{
			cout << "        Allocated Blocks are.              \n";	
			
			int j = cur->start;
			int i = 0;
			while (i<cur->fsize)
			{
				cout << j << "---->";
				j++;
				i++;
			}
			cout << endl<<endl<<endl;
			                                     //only displaying the file names and extensions if present and allocated blocks
		}
		else
		{
			cout << "       No allocated bolcks.      \n";							//flag raised if there is no such allocated block
		}
		


	}

}


HT_For_CA::~HT_For_CA()
{
	for (int i = 0; i < capacity; i++)
	{

		fNode1 *temp2;
		fNode1 *cur = htable[i];
		while (cur != NULL)
		{
			temp2 = cur;											//deletion or deallocation oh hashtable
			htable[i] = cur->Next;
			cur = htable[i];
			delete temp2;

		}
		htable[i] = NULL;
	}
	delete[] htable;
	cout << "Hash table is cleared.\n";
}

void HT_For_CA::DisplayDirectory()
{
	if (size != 0)
	{
		int j = 1;
		cout << "\t\t\t***FILES IN THE DIRECTORY ARE***\n\n";
		for (int i = 0; i < capacity; i++)
		{


			fNode1 *cur = htable[i];
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