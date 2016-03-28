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

void TriMatrix::set_A(vector<double> Upper, vector<double> Main, vector<double> Lower)
{
	int N = Upper.size();			// Define size N
	SuperDiag.resize(N);			// Set the size of the super diagonal to N
	SuperDiag = Upper;
	MainDiag.resize(N+1);			// Set the size of the main diagonal to N+1
	MainDiag = Main;
	SubDiag.resize(N);				// Set the size of the sub diagonal to N
	SubDiag = Lower;
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