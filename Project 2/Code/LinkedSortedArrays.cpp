
/* The Linked Sorted Arrays data structure will work. Assume that we have a defined constant K (which is set to 4, for illustration).
We will create an array of size K,call this array A. We will insert elements into array A and make sure the elements are kept in sorted order.
As soon as the array A of size K is filled up and we want to insert the (K+1)th element. Rather than creating a larger array,
we would create another array B (of size K); move half the elements in A into the array B such that the largest number in A is less than
the smallest number in B. The array A is now linked to array B as in a linked list. You will have to implement at least the following
two classes: SortedArray and LinkedSortedArrays in this project as described below.  During the remove operation form the array A of size K,
if the number of elements after removal becomes less than a threshold value (say K/2), then remaining elements in A are merged with either the array
that points to A or the array A points to as long as there is room in either of them. */
#include <iostream>
#include<list>
#include<cstdlib>
#include "SortedArray.cpp"

using namespace std;

template <class DT> class LinkedSortedArray {
private:
	list<SortedArray<DT> > Sa;
	int ArraySizeFactor; //The maximum size of the array in the SortedArray   

public:
	LinkedSortedArray();
	LinkedSortedArray(int C);
	virtual ~LinkedSortedArray();
	DT& find(const DT& key);
	void insert(DT& newOne);
	void remove(const DT& X);
	DT& operator[](int p);
	template<class DT>
	friend ostream& operator<<(ostream& os, LinkedSortedArray<DT>& sa);
};

template <class DT>
LinkedSortedArray<DT>::LinkedSortedArray()//default constructor
{
	ArraySizeFactor = 0;
}

template <class DT>
LinkedSortedArray<DT>::LinkedSortedArray(int K)//creates a linked sorted array with one sorted array of capacity K
{

	ArraySizeFactor = K;
	Sa.push_back(SortedArray<DT>(K)); //inserting new empty sorted array into list
}
template <class DT>
LinkedSortedArray<DT>::~LinkedSortedArray()//destructor
{
	ArraySizeFactor = 0;
	Sa.clear();  // removes all sorted arrays contained in the list
}

/*The insert method will also iterate over the linked list. We will encounter three choices: a) the element is already in the data structure
(thrown an exception), b) we find a SortedArray (in the linked list) where the element has to be inserted and has space, and c)
we find a SortedArray where the element has to be inserted, but it does not have space. Choices a) and b) are easy to handle
(and are described previously). In case of choice c), when we apply the insert method on the SortedArray object,
it will throw an exception. As soon as the exception is caught, we apply a split operation to the SortedArray object by sending a number
ArraySizeFactor/2. Now the new SortedArray object is inserted next to the linked list object (containing the SortedArray).   */
template <class DT>
void LinkedSortedArray<DT>::insert(DT& newOne)
{
	list<SortedArray<DT> >::iterator current = Sa.begin(), next = Sa.begin();
	next++;

	try
	{
		//current will advance to the next node if the element to be inserted is greater than the first element of the next node.
		while (next != Sa.end() && newOne >= (*next)[0]) //traverse to the desired list for the insertion
		{
			current = next;
			next++;
		}
		if (current->getSize() < ArraySizeFactor) //has space
		{
			current->insert(newOne);
		}
		else
		{
			SortedArray<DT>  ns = current->split(ArraySizeFactor / 2);
			if (newOne < ns[0])
				current->insert(newOne); //will throw an exception if the element already exists in the list.
			else
				ns.insert(newOne);
			Sa.insert(next, ns); // inserting new sorted array(ns) into list
		}
	}
	catch (LSAException ex)
	{
		cout << ex.getError();
	}
}

/*Remove fist finds the element to be deleted and deletes that element if it exists, during the remove operation form the array A of size K,
if the number of elements after removal becomes less than a threshold value (say K/2), then remaining elements in A are merged with either
the array that points to A or the array A points to as long as there is room in either of them. */
template <class DT>
void LinkedSortedArray<DT>::remove(const DT& X)
{
	list<SortedArray<DT> >::iterator current = Sa.begin(), prev = Sa.end(), next = Sa.end();
	int p;
	try {
		while (current != Sa.end())
		{
			if (X >= (*current)[0] && X <= (*current)[(*current).getSize() - 1]) //checking whether key is within bounds
			{
				p = (*current).find(X);
				if (X != (*current)[p])
					throw LSAException("The elemet does not exist");
				(*current).remove(X);
				break;
			}
			prev = current;
			current++;
		}

		if (current == Sa.end())
			throw LSAException("The element does not exists");
		else {
			if ((*current).getSize() < ArraySizeFactor / 2) //remove current if we can accommodate current in either of the neighbouring lists
			{
				next = current;
				next++; //points to next list
				if (prev != Sa.end() && (prev->getSize() + (*current).getSize() <= ArraySizeFactor)) // can we accommodate in Prvious list
				{
					prev->join(*current);
					Sa.erase(current); //Sorted  array is destroyed after the copy
				}
				else if (next != Sa.end() && (next->getSize() + (*current).getSize() <= ArraySizeFactor)) // can we accommodate in next list
				{
					next->join(*current);
					Sa.erase(current);	//Sorted  array is destroyed after the copy		
				}

			}

		}
	}
	catch (LSAException ex)
	{
		cout << ex.getError();
	}
}

/*The find method will start iterate over the linked list structure until either the element is found or all the nodes of the linked list
have been searched. When processing a node during the iteration, it will first check if the element we are looking for is within the
bounds of the max and min values stored in the SortedArray class object*/
template <class DT>
DT & LinkedSortedArray<DT>::find(const DT& key)
{
	list<SortedArray<DT> >::iterator current = Sa.begin();
	int p;

	try {

		while (current != Sa.end())
		{
			if (key >= (*current)[0] && key <= (*current)[(*current).getSize() - 1]) //checking whether key is within bounds
			{
				p = (*current).find(key);
				if (key != (*current)[p])
					throw LSAException("The elemet does not exist ");
				else cout << "The element exist in the list ";
				return p;
			}
			current++;

		}
		if (current == Sa.end())
			throw LSAException("The element does not exists ");
	}
	catch (LSAException ex)
	{
		cout << ex.getError();
	}

}

/* Returns the element (by box) at position index of the array. Example: Let us say that the LinkedSortedArray has two elements (A and B).
Further assume that A and B have 4 and 3 elements, respectively. If the index position specified is 0, then the [] operator should return the
first element from A. If the index position specified is a 6, it should return the third element from B (6-4 (no of elements in A) = 2).
An exception should be thrown if the index is out of bounds. */
template<class DT>
DT &LinkedSortedArray<DT>::operator[](int i)
{
	list<SortedArray<DT> >::iterator current = Sa.begin(), next = Sa.begin();
	if (i < 0)
		throw LSAException("Index out of bounds");
	while (current != Sa.end() && i >= current->getSize()) //traverse to the desired list
	{
		i = i - current->getSize();
		current++;
	}
	if (current != Sa.end())
		return (*current)[i];
	else
		throw LSAException("Index out of bounds");
}

/*Iterate over the sorted arrays in the list and print its contents*/
template <class DT>
ostream& operator<<(ostream& os, LinkedSortedArray<DT>& lsa)
{
	list<SortedArray<DT> >::iterator current = lsa.Sa.begin();
	if (current->getSize() == 0)
		cout << "Linked Sorted List is empty";
	else cout << "The contents of Linked Sorted List is:" << endl;


	while (current != lsa.Sa.end())
	{
		cout << *current; //print the sorrted array
		current++; //move  next
		cout << endl;
	}
	return os;
}