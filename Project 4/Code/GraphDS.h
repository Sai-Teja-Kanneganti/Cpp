/*Graph data structure: Graph is  represented as  adjacancy list and provides methods for adding an edge, removing an edge, listing the neighbors of a vertex,
breadth first traversal and depth first traversal of a given vertex.*/
#include<iostream>
#include<list>
#include "GraphException.cpp"
using namespace std;
class Graph
{
private:
	int numOfNodes; // Number of nodes in the graph  
	list<int> *adjList; // The adjacency list 
	bool *visited;
	int	HasEdge(int v, int w);
	void DFST(int n);//DFS Traversal	
public:
	Graph();
	Graph(int n);
	void addEdge(int v, int w); //To add a edge
	void removeEdge(int v, int w);//To remove a edge
	void listNeighbors(int n); //lists the neighors of node
	void DFS(int n); //Depth first traversal of a node n
	void BFS(int n); ///Breadth first traversal of a node n
};

//Default constructor  assigns 0 as number of nodes
Graph::Graph()
{
	numOfNodes = 0;
}

//Create a graph with n nodes
Graph::Graph(int n)
{
	numOfNodes = n;
	adjList = new list<int>[n];
}

//Iterates over  adjacent of v and searchs for w if exist returns 1 else returns 0
int Graph::HasEdge(int v, int w)
{
	list<int>::iterator current = adjList[v].begin();
	while (current != adjList[v].end())   //iterate over adjacent of  v 
	{
		if (*current == w)
			return 1;
		current++;
	}
	return 0;
}

//Adds edge by pushing w as adjacent of v. Throws exception if the edge already  exists.
void Graph::addEdge(int v, int w)
{
	if (HasEdge(v, w))
		throw GraphException("Edge already exists");
	else
	{
		adjList[v].push_back(w);  //insert w as the adjacent of  v		
	}
}

//Iterate over adjacent of v and finds w, removes it if  exits. Throws exception if it does not exists
void Graph::removeEdge(int v, int w)
{
	list<int>::iterator v_adjacnets = adjList[v].begin();

	if (!HasEdge(v, w))
		throw GraphException("Edge not exists");
	else
	{
		while (v_adjacnets != adjList[v].end() && *v_adjacnets != w) //iterate over adjacent of v and search for  w
			v_adjacnets++;
		adjList[v].erase(v_adjacnets);   //erase the  edge
	}
}

//Finds the neighbors of n and prints
void Graph::listNeighbors(int n)
{
	list<int>::iterator adjacent;
	for (adjacent = adjList[n].begin(); adjacent != adjList[n].end(); ++adjacent)
	{
		cout << *adjacent << " ";
	}
}

/*DFS is an algorithm for traversing a graph data structures. One starts at the given node n and explores as far as possible along each branch before backtracking.
First it visits the node n and fetches its adjacent node and recursivley it applies DFS on it. It uses STACK. */
void Graph::DFS(int n)
{
	visited = new  bool[numOfNodes];
	for (int i = 0; i < numOfNodes; i++)
	{
		visited[i] = false;//marking as not visited initially
	}
	DFST(n);
}

void Graph::DFST(int n)
{
	list<int>::iterator adjacent;
	if (!visited[n])
	{
		cout << n << " ";
		visited[n] = true;//marking n as visited
						  //adjacent = Neighbors(n);
		for (adjacent = adjList[n].begin(); adjacent != adjList[n].end(); ++adjacent)
		{
			if (!visited[*adjacent])
				DFST(*adjacent);
		}
	}
}

/* BFS is an algorithm for traversing graph data structures. It starts at the node n and explores all its neighbor nodes first, before moving to the next level neighbors.
We use queue in the implementation of BFS.  Fist we vist the starting node and fetch all the neighbors and visit them and enqueue them into queue, and dequeue a vertex
and apply same process  until queue becomes empty*/
void Graph::BFS(int n)
{
	// Create a BFSQueue 
	list<int> BFSQueue;

	// Mark all the vertices as not visited	
	for (int i = 0; i < numOfNodes; i++)
		visited[i] = false;

	// Mark the current node as visited and enqueue it
	visited[n] = true;
	BFSQueue.push_back(n);

	// adjacent will be used to get all adjacent vertices of a vertex n
	list<int>::iterator adjacent;

	while (!BFSQueue.empty())
	{
		// Dequeue a vertex from BFSQueue and print it
		n = BFSQueue.front();
		cout << n << " ";
		BFSQueue.pop_front();

		// Iterate over all adjacent vertices of the dequeued vertex n
		// If a adjacent has not been visited, then mark it visited and enqueue it
		for (adjacent = adjList[n].begin(); adjacent != adjList[n].end(); ++adjacent)
		{
			if (!visited[*adjacent])
			{
				visited[*adjacent] = true;
				BFSQueue.push_back(*adjacent);
			}
		}
	}
}
