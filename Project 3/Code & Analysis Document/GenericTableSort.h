/*The table (result) is sorted by the column seq[0]. Then for each of the remaining seq[j],it scans from the
beginning and finds the rows with the same values for columns seq[0] through seq[j-1] and sorts these rows. */

int * GenericTableSort(int **data, int rows, int *seq, int seq_size, void(*gSort)(int **data, int* result, int col, int begin, int end))
{
	int *result, col=0,row,begin,end,k,rowsEqual;

	result = new int[rows];

	for (int i = 0; i < rows; i++)
		result[i] = i;

	(*gSort)(data, result, seq[col], 0, rows - 1);

	for (col = 1; col < seq_size; col++)
	{
		for (row = 0; row < rows;)
		{

			begin = row;
			end = row + 1;
			rowsEqual = 1;
			
			while (rowsEqual == 1 && end < rows)
			{
				for (k = 0; k < col && end < rows && rowsEqual == 1; k++) //Columns already sorted are compared for equality with respect to begin and end
				{
					if (data[result[begin]][seq[k]] != data[result[end]][seq[k]])
						rowsEqual = 0;
				}
				if (rowsEqual == 1)
				{
					end++;					
				}
			}
			
			(*gSort)(data, result, seq[col], begin, end - 1);

			row = end;
		}

	}
	return result;
}
