/* Merge Sort is a Divide and Conquer algorithm. In merge sort, first it divides the list into half and then then these sub lists are further divided 
into half until each sub list contains only one element (Means sorted). Then these sub lists are repeatedly merged with Merge algorithm to produce the
sorted list.*/

/*Merge: Merges two sorted list into single sorted array: begin to mid is one list and mid+1 to end is another list.
It uses temporary array.*/
void merge(int **data, int* result, int col, int begin, int end, int mid)
{
	int i, j, k, *temp;
	i = begin; // i is index of first array
	k = 0;    // k is index for temporary array
	j = mid + 1; //j is index of second array
	temp = new int[end- begin + 1]; //Initializing temporary array with size to hold elements from begin to end

	while (i <= mid && j <= end) //compare both lists, if elements presents in both.
	{
		if (data[result[i]][col] < data[result[j]][col]) //Copy element from fist array if it is lessthan second
		{
			temp[k] = result[i];
			k++;
			i++;
		}
		else                                            //Otherwise copy element from second array 
		{
			temp[k] = result[j];
			k++;
			j++;
		}
	}

	while (i <= mid) //copy all elements of first list, if exists.
	{
		temp[k] = result[i];
		k++;
		i++;
	}

	while (j <= end) //copy all elements of second list, if exists.
	{
		temp[k] = result[j];
		k++;
		j++;
	}
	for (i = 0; i < k; i++) //copy elements from temporary array to original array.
	{
		result[i+begin] = temp[i];
	}
}

void mergesort(int **data, int* result, int col, int begin, int end)
{
	int mid;
	if (begin < end)
	{
		mid = (begin + end) / 2; //Divide the list into half
		mergesort(data, result, col, begin, mid);    //Recursively apply mergesort on left list
		mergesort(data, result, col, mid + 1, end);  //Recursively apply mergesort on left list
		merge(data, result, col, begin, end, mid);	 //Merge the sorted lists into one sorted list
	}
	return;
}