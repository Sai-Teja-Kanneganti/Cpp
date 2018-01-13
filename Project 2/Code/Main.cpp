/*Main program, which reads input from p2input.txt, creates instance for class LinkedSortedArray
with a capacity and performs operations specified in the input file*/
#include <iostream>
#include<list>
#include<cstdlib>
#include "LinkedSortedArrays.cpp"
using namespace std;

// to prevent data contamination from previous use
void cleanString(char* token, int size)
{
	for (int i = 0; i < size; i++)
	{
		token[i] = '\0';
	}
}

int getNextToken(char* buffer, char* token, int startPos, int bufSize, int tokenSize, char delimiter)
{
	int i, j;

	cleanString(token, tokenSize);

	i = startPos;
	j = 0;

	// Skip any blanks
	while ((buffer[i] == ' ') && (i < bufSize))
	{
		i++;
	}

	if (i < 256)
	{
		while ((buffer[i] != delimiter) && (i < 256) && (j < tokenSize))
		{
			token[j++] = buffer[i++];
		}
	}
	return i;
}

int main()
{
	char buffer[256];
	char ivalue[20], ch;
	char blank = ' ';
	char command[1];
	int number, capacity, index;
	cin.getline(buffer, 256);
	index = getNextToken(buffer, ivalue, 0, 256, 20, blank);
	capacity = atoi(ivalue); //get the capasity of the Sorted Array
	LinkedSortedArray<int> lsa(capacity); //create an instance for Linked Sorted array with capasity

	while (!cin.eof())
	{
		cin.getline(buffer, 256);
		index = getNextToken(buffer, command, 0, 256, 1, blank);
		switch (command[0])
		{
		case 'I':	//perform insert operation				
			index = getNextToken(buffer, ivalue, index, 256, 20, blank);
			number = atoi(ivalue);
			lsa.insert(number);
			break;
		case 'R':	//perform read operation			
			index = getNextToken(buffer, ivalue, index, 256, 20, blank);
			number = atoi(ivalue);
			lsa.remove(number);
			break;
		case 'F':	//perform find operation				
			index = getNextToken(buffer, ivalue, index, 256, 20, blank);
			number = atoi(ivalue);
			lsa.find(number);
			break;
		case 'O':	//perform output operation
			cout << endl << "OUTPUT :";
			cout << endl << lsa;
			break;

		default:
			break;
		}

	}

	return 0;
}
