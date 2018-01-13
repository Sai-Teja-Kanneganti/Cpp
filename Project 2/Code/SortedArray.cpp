/*SortedArray class is used to store an array of a defined size (decided at runtime this is the number K), the size of the array (K),
and the number of elements currently in the array as below. The elements are stored in sorted order in the array.
The elements are not by themselves stored in the array, but rather pointers to the elements are stored.  */
#include<iostream>
#include"LSAException.cpp"
using namespace std;
template <class DT>
class SortedArray
{
private:
	int capacity;   // capacity, which is K      
	int size;   // num. of elements stored      
	DT* elements;   // array used to store the elements, size of K  

public:

	SortedArray();
	SortedArray(int K);
	int getSize();
	DT& find(const DT& lookFor);
	void insert(DT& newElement);
	void remove(const DT& oldElement);
	SortedArray<DT>& split(int k);
	void join(SortedArray<DT>& P);
	DT& operator[](int i);
	template<class DT>
	friend ostream& operator<<(ostream& os, SortedArray<DT>& sa);

};



template <class DT>
SortedArray<DT>::SortedArray()//default constructor
{
	capacity = 0;
}

template <class DT>
SortedArray<DT>::SortedArray(int K)//constructor to  create a sorted array of capacity K
{
	capacity = K;
	elements = new DT[K];
	size = 0;
}


//gets the size of  sorted list
template <class DT>
int SortedArray<DT>::getSize()
{
	return size;
}

/* Throw an exception if there is no room to insert into the array, or an object with the same value is already stored in the array.
Otherwise, it inserts newElement in the sorted order. Make sure to perform a binary search to determine if the element is already
stored and to locate the position where to insert the element to. */
template <class DT>
void SortedArray<DT> ::insert(DT& newElement)
{
	int p;
	if (size == 0)
	{
		elements[0] = newElement;
		size++;
	}
	else if (size == capacity)
		cout << "LIST is FULL";
	else {

		p = find(newElement); //search the position for newElement
		if (p < size && newElement == elements[p])
			throw LSAException("The element already exists");
		for (int k = size; k > p; k--) //moves elements to one location ahead and accomodates space for new element
			elements[k] = elements[k - 1];
		elements[p] = newElement;   //inserting new element at location p		
		size++;
	}
}

/*Throw an exception if the element is not present in the array, otherwise it removes the element by shifting the elements to the left.
Use binary search to find the element. */
template <class DT>
void SortedArray<DT> ::remove(const DT& newElement)
{
	int p;
	if (size == 0)
	{
		throw LSAException("The Sorted List is Empty");
	}
	else
	{
		p = find(newElement);
		if ((p < size && newElement != elements[p]) || p == size) // if element does not exists
			throw LSAException("The element does not exists");

		//remove element at p location
		for (int i = p; i < size - 1; i++)   //move elements
			elements[i] = elements[i + 1];
		size--;  //decrease the size

	}
}

/* Performs binary search to return the reference to the element at the location*/
template <class DT>
DT& SortedArray<DT>::find(const DT& lookFor)
{
	int low = 0, high = size - 1, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (lookFor == elements[mid])
			return mid;
		else if (lookFor < elements[mid])
			high = mid - 1;
		else low = mid + 1;
	}
	return low;
}

/* Returns a SortedArray containing elements from position i through the last element of the array. The elements from i through
the last element are removed from this array and adjust the variable size of this array. */
template<class DT>
SortedArray<DT>& SortedArray<DT>::split(int k)
{
	SortedArray<DT> newSA(capacity);
	for (int i = k; i < size; i++)
	{
		newSA.elements[i - k] = elements[i];     // copies elements from k to size-1 to new array
	}
	newSA.size = size = k; //initializing sizes of new and old arrays to k
	return newSA;
}

/*Copies the elements from array P to this array making surethat the elements are in sorted array. */
template<class DT>
void SortedArray<DT>::join(SortedArray<DT>& s)
{
	for (int i = 0; i < s.size; i++)
	{
		elements[size + i] = s.elements[i];    //copying elements of s
	}
	size = size + s.size; //calulates the new size after join

}

/*Return the element, which is at index i*/
template<class DT>
DT &SortedArray<DT>::operator[](int i)
{
	if (i >= size || i < 0)
	{
		throw LSAException("Index out of bounds error");
	}
	return elements[i];
}

/*Display the contents of a given sorted array*/
template <class DT>
ostream&   operator<<(ostream& os, SortedArray<DT>& sa)
{

	for (int k = 0; k < sa.size; k++)
		os << sa[k] << "  ";

	return os;
}