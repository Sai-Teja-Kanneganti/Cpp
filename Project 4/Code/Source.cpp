/*Main program, which reads input from p4input.txt, creates instance for class Graph
with a number of nodes and performs operations specified in the input file*/
#include <iostream>
#include<cstdlib>
#include "GraphDS.h"
using namespace std;

// to prevent data contamination from previous use
void cleanString(char* token, int size)
{
	for (int i = 0; i < size; i++)
	{
		token[i] = '\0';
	}
}

//Gets next token from buffer from start position.
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
	char ivalue[20];
	char blank = ' ';
	char command[10];
	int v, w, n, numOfNodes, index;
	cin.getline(buffer, 256);
	index = getNextToken(buffer, ivalue, 0, 256, 10, blank);

	numOfNodes = atoi(ivalue); //get the numbers of nodes of the Graph

	Graph G(numOfNodes); //creating the instance for the Graph
	while (!cin.eof())
	{
		cin.getline(buffer, 256);
		index = getNextToken(buffer, command, 0, 256, 10, blank);
		switch (command[0])
		{
		case 'A':	//Add edge			
			index = getNextToken(buffer, ivalue, index, 256, 10, blank);
			v = atoi(ivalue);
			index = getNextToken(buffer, ivalue, index, 256, 10, blank);
			w = atoi(ivalue);
			try
			{
				G.addEdge(v, w);
			}
			catch (GraphException e)
			{
				cout << endl << e.getError();
			}
			break;
		case 'R':	//Remove edge			
			index = getNextToken(buffer, ivalue, index, 256, 10, blank);
			v = atoi(ivalue);
			index = getNextToken(buffer, ivalue, index, 256, 10, blank);
			w = atoi(ivalue);
			try
			{
				G.removeEdge(v, w);
			}
			catch (GraphException e)
			{
				cout << endl << e.getError();
			}
			break;
		case 'L':	//List the neighbors				
			index = getNextToken(buffer, ivalue, index, 256, 10, blank);
			n = atoi(ivalue);
			cout << endl << "Neighbors of: " << n << endl;
			G.listNeighbors(n);
			break;
		case 'B':	//BFS on n
			index = getNextToken(buffer, ivalue, index, 256, 10, blank);
			n = atoi(ivalue);
			cout << endl << "Breadth First Search traversal of: " << n << endl;
			G.BFS(n);
			break;
		case 'D':	//DFS on n
			index = getNextToken(buffer, ivalue, index, 256, 10, blank);
			n = atoi(ivalue);
			cout << endl << "Depth First Search traversal of: " << n << endl;
			G.DFS(n);
			break;

		default:
			break;
		}

	}

	return 0;
}
