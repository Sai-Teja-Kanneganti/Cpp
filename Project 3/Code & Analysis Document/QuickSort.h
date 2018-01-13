/*Quicksort is a divide and conquer algorithm. Picks an element, called a pivot (here the first element), from the array. 
Partitions the array such that all elements which are less than or equal to the pivot are moved to the left side of pivot a
nd all elements which are greater than the pivot are moved to right side of pivot. After this partitioning, the pivot is sorted. 
Recursively the same process is applied on the left side of pivot and right side of the pivot until each sub list contains one element (means sorted).*/

void swap(int i, int j, int **a, int* result, int col) //interchanges row indices in result  array
{
	int temp = result[i];
	result[i] = result[j];
	result[j] = temp;
}

int partition(int **data, int* result, int col, int begin, int end)
{
	int pivot = data[result[begin]][col];
	int i = begin;
	int j = end;

	while (i <= j)
	{
		while (i <= j && data[result[i]][col] <= pivot) // moving from left
			i++;
		while (i <= j && data[result[j]][col] > pivot)  // moving from right
			j--;
		if (i < j){
			swap(i, j, data, result, col); 
			i++;
			j--;
		}
	}

	swap(begin, j, data, result, col);

	return j;
}

void quicksort(int **data, int* result, int col, int begin, int end)
{
	int pos;//to hold position of pivot
	if (begin < end)
	{
		pos = partition(data, result, col, begin, end); //Apply partition and gets the position(j) of pivot after partition.
		quicksort(data, result, col, begin, pos - 1);   //Recursively apply quick sort on left side of pivot.
		quicksort(data, result, col, pos + 1, end);     //Recursively apply quick sort on right side of pivot.
	}	
}

