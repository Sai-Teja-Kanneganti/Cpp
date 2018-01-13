/*  A bubble sort, also called a sinking sort or exchange sort, it performs n-1 iterations, in each iteration it compares all adjacent pairs and swaps them if necessary, causing the elements to "bubble" up toward their proper position. The process continues until no swaps are necessary or all n-1 iteration are exhausted. */

void bubblesort(int **data, int* result, int col, int begin, int end)
{
	int SwapDone = 1;
	for (int i = begin; i < end && SwapDone == 1; i++) //perform n-1 iterations or  stop when there is no swap.
	{
		SwapDone = 0; // Swap not done
		for (int j = begin; j < (begin + end - i); j++) //comparing adjacent elements in each iteration.
		{
			if (data[result[j]][col] > data[result[j + 1]][col]) //comparing adjacent elements.
			{
				int temp = result[j];
				result[j] = result[j + 1];
				result[j + 1] = temp;
				SwapDone = 1; // Swap done
			}
		}
	}

}

