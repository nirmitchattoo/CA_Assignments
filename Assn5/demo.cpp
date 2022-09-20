#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;

void luDecompositionAlgo(int A[][MAX],int B[], int n)
{
    // Decomposing matrix into Upper and Lower matrix
    //AX = B
    //A = LU
    //LUX = B
    //Lets say UX as Y
    //So, LY = B
    //After finding the Y by using above equation we can put it in UX = Y and we can calculate our required X

    
	int lower[n][n], upper[n][n];
	memset(lower, 0, sizeof(lower));
	memset(upper, 0, sizeof(upper));

	for (int i = 0; i < n; i++)
	{
		// Upper Triangular
		for (int k = i; k < n; k++)
		{
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower[i][j] * upper[j][k]);

			upper[i][k] = A[i][k] - sum;
		}

		// Lower Triangular
		for (int k = i; k < n; k++)
		{
			if (i == k)
				lower[i][i] = 1; 
			else
			{
				int sum = 0;
				for (int j = 0; j < i; j++)
					sum += (lower[k][j] * upper[j][i]);

				lower[k][i]
					= (A[k][i] - sum) / upper[i][i];
			}
		}
	}


	// Displaying the upper and lower triangular matrix
	for (int i = 0; i < n; i++)
	{
		// Lower
		for (int j = 0; j < n; j++)
			cout << setw(6) << lower[i][j] << "\t";
		cout << "\t";

		// Upper
		for (int j = 0; j < n; j++)
			cout << setw(6) << upper[i][j] << "\t";
		cout << endl;
	}


    //For calculating y by using the equation LY = B
    int ans1[n];
    //Iterating over all the rows of lower 
    for(int i = 0;i<n;i++){
        int sum = 0;
        for(int j = 0;j<i;j++){
            sum += lower[i][j]*ans1[j];
        }
        //Check the condition for avoiding arithmetic exception
        if(lower[i][i]!=0){
            ans1[i] = (B[i]-sum)/lower[i][i];
        }
        else{
            ans1[i] = 0;
        }
    }


    //For calculatig x by using the UX = Y
    double ans2[n];
    //Iterate over all the rows of upper triangular matrix
    for(int i = n-1;i>=0;i--){
        int sum = 0;
        for(int j = n-1;j>i;j--){
            sum += upper[i][j]*ans2[j];
        }
        //Check the condition for avoiding arithmetic exception
        if(upper[i][i]!=0){
            ans2[i] = float((ans1[i]-sum)/upper[i][i]);
        }
        else{
            ans2[i] = 0;
        }
    }
    for(int i = 0;i<n;i++){
        cout<<ans2[i]<<" "<<endl;
    }
}

void inputMatrix(int mat[][MAX],int n){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cin>>mat[i][j];
        }
    }
}

int main()
{
    int n;
    cout<<"Enter the number of areas:- "<<endl;
    cin>>n;
	int mat[MAX][MAX];
    int B[n];
    inputMatrix(mat,n);
    for(int i = 0;i<n;i++){
        cin>>B[i];
    }
	luDecompositionAlgo(mat, B, n);
	return 0;
}