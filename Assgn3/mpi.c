/*
NAME: NIRMIT CHATTOO
PRN: 2020BTEIT00001
SUBJECT: COMPUTER ALGORITHM LAB
ASSIGNMENT NO. 3
*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

// Pre-function declarations
void sendItemsDetails(int *arr, int n, int size, int rank); // This functions is to send items details from a branch office to head office.
void receiveItemDetails(int my_rank);												// It's is used by branch office to recieve the expenses details by a head office.
// void sendExpenses(int sum, int size); // This function is used by Head office to send the details of the branches given by each branch. office.
void receiveExpenses(int my_rank, int size); // This function is used by Head office to receive the expeneses of the each branch office.

// Main function is used to distribute all the work.

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv); // Initializing the MPI environment.

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Storing rank of each processor in the rank variable.
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Storing the size of each processor in the size variable.

	if (rank == 0)
	{ // Checking if the rank is equal to zero if yes then this is Head office processor.
		receiveExpenses(rank, size);
		// sendExpenses(0, size);
	}
	else
	{ // Else it is branch office.
		int n = 5;
		int arr[n]; // Creating the expenses array of size 8, which means there are 8 different items to be sold by the branch office.
		printf("Items with expenses for Branch Office No. %d\n", rank);
		for (int i = 0; i < n; i++)
		{
			arr[i] = i + rank; // here the price of each item is filled.
			printf("%dth item has price -> %d\n", i, arr[i]);
		}

		sendItemsDetails(arr, n, size, rank);
		receiveItemDetails(rank);
	}

	MPI_Finalize(); // Ending the MPI environment.
}

void sendItemsDetails(int *arr, int n, int size, int rank)
{
	// printf("Branch Send\n");
	MPI_Send(arr, n, MPI_INT, 0, 8, MPI_COMM_WORLD); // here the each branch office will send the details to the head office.
}

void receiveItemDetails(int my_rank)
{
	// printf("Branch Receive\n");
	int arr[6];
	MPI_Status status;
	MPI_Recv(arr, 6, MPI_INT, 0, 8, MPI_COMM_WORLD, &status); // here the branch office will receive the data from the head office.

	printf("Total expense of Branch %d is %d\n", my_rank, arr[5]);
}

// void sendExpenses(int sum, int size){
// printf("Head Office send\n");
//}

void receiveExpenses(int my_rank, int size)
{ // Receiving the expenses from the branch office.
	// printf("Head Office Receive\n");
	int arr[6];
	MPI_Status status;
	for (int i = 1; i < size; i++)
	{
		MPI_Recv(arr, 5, MPI_INT, i, 8, MPI_COMM_WORLD, &status);

		int sum = 0;
		for (int i = 0; i < 5; i++)
		{
			sum += (arr[i] * (i + 1));
		}
		arr[5] = sum;
		MPI_Send(arr, 6, MPI_INT, i, 8, MPI_COMM_WORLD);
	}
}
