/*This method will create a 2 dimensional array if the size is M x 4. Where M is number  of rows. 
Then populate data into these “surveys” using the following algorithm: */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

int** gen_data(int M)
{
	int **data;

	data = new int*[M];  // M rows 
	for (int i = 0; i< M; i++) //Allocating memory for M rows in data
		data[i] = new int[4];

	srand(time(NULL));  //initializing with time.

	for (int i = 0; i < M; i++)
	{
		data[i][0] = rand() % 41 + 20;		//Age between 20 and 60
		data[i][1] = rand() % 2 + 0;		//Gender between 0 and 1
		data[i][2] = rand() % 2000 + 73000; //ZipCode between 73000 and 73999
		data[i][3] = rand() % 101 + 100;	//Weight between 100 and 200
	}

	return data;
}