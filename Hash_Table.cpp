#include"HashTable.h"
#include<iostream>
using namespace std;
void Hash_Table::SplitString(char *str, char *F,char *E)
{
	int i = 0;
	while (str[i] != '.')
	{
		F[i] = str[i];
		i++;
	}
	F[i] = '\0';
	i++;
	int j = 0;														//Function to split the string into substrings
	while (str[i] != '\0')
	{
		E[j] = str[i];
		i++;
		j++;
	}
	E[j] = '\0';
}



int Hash_Table::Hash_Function(char *fileN)
{
	int sum = 0;
	for (int i = 0; fileN[i] != '\0'; i++)
	{
		sum += int(fileN[i]);										//Function to calculate the sum 
	}
	return (sum%capacity);
}


void Hash_Table::copystr(char *f7, char *p)
{
	int i = 0;
	while (p[i] != '\0')
	{
		f7[i] = p[i];												//Copying of one array into another
		i++;
	}
	f7[i] = p[i];
}

void Hash_Table:: combineStrings(char *F, char *E, char *t)
{
	int i;
	for (i = 0; F[i] != '\0'; i++)
	{
		t[i] = F[i];
	}
	t[i] = '.';														//Combining the two string that have been made i.e E and F
	i++;
	for (int j = 0; E[j] != '\0'; j++)
	{
		t[i] = E[j];
		i++;
	}
	t[i] = '\0';

}

void Hash_Table::DisplayDisk()
{
	for (int i = 0; i < 64; i++)
	{
		cout << Disk[i] << " ";
	}
	cout << endl;
}