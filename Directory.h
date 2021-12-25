#ifndef DIRECTORY_H
#define DIRECTORY_H
#include"HT_For_CA.h"
#include"LinkedAllocation.h"
#include"IndexedAllocation.h"
//#include"HashTable.h"
#include<iostream>
using namespace std;
class Directory
{
	HT_For_CA *Cont;
	LinkedList_Allocation *Link;
	Indexed_Allocation *Ind;
public:
	Directory()
	{
		Cont = NULL;
		Link = NULL;
		Ind = NULL;
	}
	void ChooseAllocation()
	{
		short choice;
		cout << "Enter 1 for contigous allocation.\nEnter 2 for LinkedList allocation.\nEnter 3 for Indexed allocation.\n";
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice == 1)
		{
			CA_Operations();
		}
		else if (choice == 2)
		{
			LLA_Operations();
		}
		else if (choice == 3)
		{
			IA_Operations();
		}

	}
	short Menu()
	{
		
		short choice;
		cout << "\t\t\t\t######### FILE DIRECTORY SYSTEM ##########\n\n\n\n";
		cout << "*******************************************************************************************\n";
		cout << "*		    Enter 1 for Initializing  hash table.										   *\n";
		cout << "*			Enter 2 for Inserting the file in Htable and allocate space in disk.		   *\n";
		cout << "*			Enter 3 for Displaying whole directory.										   *\n";
		cout << "*			Enter 4 for display a file.                                                    *\n";
		cout << "*			Enter 5 for deleting a file from directory.                                    *\n";
		cout << "*			Enter 6 for deallocating file blocks.                                          *\n";
		cout << "*			Enter 7 for checking free space in disk.                                       *\n";
		cout << "*			Enter 8 for checking number of files ih your directory.                        *\n";
		cout << "*			Enter 9 for displaying a disk.                                                 *\n";
		cout << "*			Enter 10 for delete a file through minheap.                                    *\n";
		cout << "*			Enter -1 for Exit.                                                             *\n";
		cout << "*******************************************************************************************\n";
		cout << " 			Enter your choice.";
		cin >> choice;

		system("cls");

		return choice;
	}
	void CA_Operations()
	{
		Cont = new HT_For_CA;
		short choice = Menu();
		while (choice != -1)
		{
			if (choice == 1)
			{
				int size;
				cout << "Please...Enter size of hash_table.\n";
				cin >> size;                                          //Under construction
				Cont->InitializeTable(size);
			}
			else if (choice == 2)
			{
				char F[25]; char E[5]; int size;
				cin.ignore();
				cout << "Enter a file name.\n";
				cin.getline(F, 25);
				cout << "Enter extention.\n";
				cin.getline(E, 5);
				cout << "Enter size of the file.\n";
				cin >> size;
				Cont->Insert(F, E, size);
			}
			else if (choice == 3)
			{
				Cont->DisplayDirectory();
			}
			else if (choice == 4)
			{
				char F[30];
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.ignore();
				cin.getline(F, 30);
				Cont->display(F);
			}
			else if (choice == 5)
			{
				char F[30];
				cin.ignore();
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.getline(F, 30);
				Cont->DeleteFile(F);
			}
			else if (choice == 6)
			{
				char F[30];
				cin.ignore();
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.getline(F, 30);
				Cont->Deallocation(F);
			}
			else if (choice == 7)
			{
				cout << "Free blocks in disk are " << Cont->getFreeSpace() << endl;
			}
			else if (choice == 8)
			{
				cout << "Number of files in hash table are  " << Cont->getSize() << endl;
			}
			else if (choice == 9)
			{
				cout << "Blocks of Disk.\n ";
				Cont->DisplayDisk();
			}
			else if (choice == 10)
			{
				////////
			}
			choice = Menu();
		}

	}



	void LLA_Operations()
	{
		Link = new LinkedList_Allocation;
		
		short choice = Menu();
		while (choice != -1)
		{
			if (choice == 1)
			{
				int size;
				cout << "Please...Enter size of hash_table.\n";
				cin >> size;                                          //Under construction
				Link->InitializeTable(size);
			}
			else if (choice == 2)
			{
				char F[25]; char E[5]; int size;
				cin.ignore();
				cout << "Enter a file name.\n";
				cin.getline(F, 25);
				cout << "Enter extention.\n";
				cin.getline(E, 5);
				cout << "Enter size of the file.\n";
				cin >> size;
				Link->Insert(F, E, size);
			}
			else if (choice == 3)
			{
				Link->DisplayDirectory();
			}
			else if (choice == 4)
			{
				char F[30];
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.ignore();
				cin.getline(F, 30);
				Link->display(F);
			}
			else if (choice == 5)
			{
				char F[30];
				cin.ignore();
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.getline(F, 30);
				Link->DeleteFile(F);
			}
			else if (choice == 6)
			{
				char F[30];
				cin.ignore();
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.getline(F, 30);
				Link->Deallocation(F);
			}
			else if (choice == 7)
			{
				cout << "Free blocks in disk are " << Link->getFreeSpace() << endl;
			}
			else if (choice == 8)
			{
				cout << "Number of files in hash table are  " << Link->getSize() << endl;
			}
			else if (choice == 9)
			{
				cout << "Blocks of Disk.\n ";
				Link->DisplayDisk();
			}
			else if (choice == 10)
			{
				////////
			}
			choice = Menu();
		}

	}



	void IA_Operations()
	{
		Ind = new Indexed_Allocation;

		short choice = Menu();
		while (choice != -1)
		{
			if (choice == 1)
			{
				int size;
				cout << "Please...Enter size of hash_table.\n";
				cin >> size;                                          //Under construction
				Ind->InitializeTable(size);
			}
			else if (choice == 2)
			{
				char F[25]; char E[5]; int size;
				cin.ignore();
				cout << "Enter a file name.\n";
				cin.getline(F, 25);
				cout << "Enter extention.\n";
				cin.getline(E, 5);
				cout << "Enter size of the file.\n";
				cin >> size;
				Ind->Insert(F, E, size);
			}
			else if (choice == 3)
			{
				Ind->DisplayDirectory();
			}
			else if (choice == 4)
			{
				char F[30];
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.ignore();
				cin.getline(F, 30);
				Ind->display(F);
			}
			else if (choice == 5)
			{
				char F[30];
				cin.ignore();
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.getline(F, 30);
				Ind->DeleteFile(F);
			}
			else if (choice == 6)
			{
				char F[30];
				cin.ignore();
				cout << "Enter Name of the File with extn i-E AB.txt.\n";
				cin.getline(F, 30);
				Ind->Deallocation(F);
			}
			else if (choice == 7)
			{
				cout << "Free blocks in disk are " << Ind->getFreeSpace() << endl;
			}
			else if (choice == 8)
			{
				cout << "Number of files in hash table are  " << Ind->getSize() << endl;
			}
			else if (choice == 9)
			{
				cout << "Blocks of Disk.\n ";
				Ind->DisplayDisk();
			}
			else if (choice == 10)
			{
				////////
			}
			choice = Menu();
		}

	}

};
#endif