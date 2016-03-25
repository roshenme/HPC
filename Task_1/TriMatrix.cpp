////////////////////////////////////////////
////// TriMatrix Class Implementation //////
////////////////////////////////////////////

#include<iostream>
#include<vector>
#include "TriMatrix.h"	// Include the class header file

using namespace std;

// TriMatrix class constructor

TriMatrix::TriMatrix() {}

// Set the coefficient matrix A

void TriMatrix::set_A(float v, float N)
{
	vector<double> Q(N + 1);		// Initialise a vector to be used to populate the diagonals

	Q[0] = 0;						// Set its first value to zero
	Q[N] = 0;						// Set its last value to zero	
	for (int i = 1; i<N; i++)
	{
		Q[i] = -2 * v;				// These values will make up the main diagonal except the first an last values
	}
	
	// Populate the main diagonal using the Q vector

	MainDiag.resize(N + 1);			// Set the size of the main diagonal to N+1		
	for (int i = 0; i<N + 1; i++)
	{
		MainDiag[i] = 1 + Q[i];		// Populate the diagonal in a loop
	}

	// Populate the super and sub diagonals

	SuperDiag.resize(N);			// Set the size of the super diagonal to N		

	SuperDiag[0] = 0;				// The first value of the super diagonal is 0
	SuperDiag[N - 1] = v;			// The last value of the super diagonal is v

	SubDiag.resize(N);				// Set the size of the sub diagonal to N

	SubDiag[0] = v;					// The first value of the sub diagonal is v
	SubDiag[N - 1] = 0;				// The last value of the sub diagonal is 0
	
	// Fill the rest of the values with v in a loop

	for (int i = 1; i<N - 1; i++)
	{
		SuperDiag[i] = v; 
		SubDiag[i] = v;
	}
}

// Implement matrix-vector multiplicaton to get the temperature vector

vector<double> TriMatrix::get_U(vector<double> u)
{
	int N = u.size();				// Assign the size of U as variable N
	vector<double> Un(N);			// Declare vector Un as size N

	//Set the first and last values of Un as the same as U

	Un[0] = u[0];					// Set the first value
	Un[N - 1] = u[N - 1];			// Set the last value

	// Do the matrix-vector multiplication in a loop
	// For each i, multiply the respective elements from the 3 diagonals of the coefficient
	// matrix A and the corresponding elements from the temperature vector U; as if matrix   
	// A was written as size (N+1 x N+1) with the main, super and sub diagonals and 
	// multiplied by the temperature vector U of size (N+1,1)

	for (int i = 1; i < N - 1; i++)
	{
		Un[i] = (SuperDiag[i] * u[i + 1]) + (MainDiag[i] * u[i]) + (SubDiag[i - 1] * u[i - 1]);
	}
	return Un;
}

// TriMatrix class destructor

TriMatrix::~TriMatrix() {}