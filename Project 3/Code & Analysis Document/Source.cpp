#include <windows.h> 
#include <iostream> 
#include <cstdio> 
#include "DataGen.h"
#include "BubbleSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "GenericTableSort.h"

using namespace std;

int main(int argc, char* argv[])
{
	int** data; 
	int rows; 
	int* seq; 
	int seq_size;
	int* bubble_result;
	int* quick_result;
	int* merge_result;
	
	LARGE_INTEGER start[3], stop[3]; // 
	if (argc != 2) 
	{ 
		cout << "Usage: project5.exe [rows]" << endl;
		exit(0); 
	}
	rows = atoi(argv[1]);
	// generate data 
	data = gen_data( rows); 	

	if (rows <= 20) // print out the raw data for small data set. 
	{ 
		cout << "Raw data: " << endl; 
		cout << "=====================================" << endl; 
		for( int i=0; i< rows; i++)        
			cout << i << ")\t"<< data[i][0] << " " << data[i][1] << " "   
			     << data[i][2] << " " << data[i][3] << endl; 
		cout << "=====================================" << endl; 
	} 

	// generate the sequence of columns for table sorting 
	if (rows <= 20) 
	{
		seq_size = 2; 
		seq = new int[seq_size]; 
		seq[0] = 1; // by gender first 
		seq[1] = 0; // then by age 
	} 
	else 
	{ 
		seq_size = 4; 
		seq = new int[seq_size]; 
		seq[0] = 2; // by zip code first 
		seq[1] = 0; // then by age 
		seq[2] = 1; // then by gender 
		seq[3] = 3; //then by weight 
	}
			
	QueryPerformanceCounter(&start[0]);
	bubble_result = GenericTableSort(data, rows, seq, seq_size, bubblesort);
	QueryPerformanceCounter(&stop[0]);
	QueryPerformanceCounter(&start[1]);
	quick_result = GenericTableSort(data, rows, seq, seq_size, quicksort);
	QueryPerformanceCounter(&stop[1]);
	QueryPerformanceCounter(&start[2]);
	merge_result = GenericTableSort(data, rows, seq, seq_size, mergesort);
	QueryPerformanceCounter(&stop[2]);

	if (rows <= 20)
	{
		cout << "Table Sorting Result: " << endl;
		for (int i = 0; i < rows; i++)
			cout << bubble_result[i] << " ";
		cout << endl;
		for (int i = 0; i < rows; i++)
			cout << quick_result[i] << " ";
		cout << endl;  
		for (int i = 0; i < rows; i++)
			cout << merge_result[i] << " ";
		cout << endl;
		cout << "======================================================================" << endl;
		cout << "Bubble\t\t\tQuick\t\t\tMerge" << endl; cout << "======================================================================" << endl;  
				
		for (int i = 0; i < rows; i++)
					cout << data[bubble_result[i]][0] << " " << data[bubble_result[i]][1] << " "
						 << data[bubble_result[i]][2] << " " << data[bubble_result[i]][3] << "\t\t"
						 << data[quick_result[i]][0] << " " << data[quick_result[i]][1] << " " 
						 << data[quick_result[i]][2] << " " << data[quick_result[i]][3] << "\t\t" 
						 << data[merge_result[i]][0] << " " << data[merge_result[i]][1] << " "
						 << data[merge_result[i]][2] << " " << data[merge_result[i]][3] << endl; 
				cout << "======================================================================" << endl;
	}
	// print out the time taken    
	cout << "Bubble\t\t\tQuick\t\t\tMerge" << endl;

	for (int i = 0; i < 3; i++)
		cout << stop[i].QuadPart - start[i].QuadPart << "\t\t\t";
		cout << "(time)" << endl;

	// releasing memory allocated for      
	// data, bubble_result, quick_result, merge_result and seq 
	delete[] bubble_result;
	delete[] quick_result;
	delete[] merge_result;
	for (int i = 0; i < rows; i++)
	{
		delete[] data[i];
	}
	delete[] data;


	getchar();
						
	return 0;
}