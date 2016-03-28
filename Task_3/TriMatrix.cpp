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

void TriMatrix::set_A(vector<double> UpperA, vector<double> MainA, vector<double> LowerA)
{
	int N = UpperA.size();			// Define size N
	SuperDiagA.resize(N);			// Set the size of the super diagonal to N
	SuperDiagA = UpperA;
	MainDiagA.resize(N+1);			// Set the size of the main diagonal to N+1
	MainDiagA = MainA;
	SubDiagA.resize(N);				// Set the size of the sub diagonal to N
	SubDiagA = LowerA;
}

// Set the coefficient matrix B

void TriMatrix::set_B(vector<double> UpperB, vector<double> MainB, vector<double> LowerB)
{
	int N = UpperB.size();			// Define size N
	SuperDiagB.resize(N);			// Set the size of the super diagonal to N
	SuperDiagB = UpperB;
	MainDiagA.resize(N + 1);			// Set the size of the main diagonal to N+1
	MainDiagB = MainB;
	SubDiagB.resize(N);				// Set the size of the sub diagonal to N
	SubDiagB = LowerB;
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
		Un[i] = (SuperDiagA[i] * u[i + 1]) + (MainDiagA[i] * u[i]) + (SubDiagA[i - 1] * u[i - 1]);
	}
	return Un;
}

// Operator overloading to overload the forward slash operator

vector<double> TriMatrix::operator/(vector<double> U)
{
	double m;						// Declare the variable m to be used in Thomas Algorithm
	int N = U.size();				// Define the size of the input vector from main
	std::vector<double> x(N);		// Initialize the x vector to hold the solutions
	vector<double> c = SuperDiagB;	// Define vector c as the super diagonal of the coefficient matrix
	vector<double> b = MainDiagB;	// Define vector b as the main diagonal of the coefficient matrix
	vector<double> a = SubDiagB;	// Define vector a as the sub diagonal of the coefficient matrix
	vector<double> d = U;			// Define vector d as the RHS vector (solution vector of time step k)

	// Loop for the forward elimination phase

	for (int i = 1; i < N; i++)
	{
		m = a[i - 1] / b[i - 1];	// Calculate the m variable 
		b[i] = b[i] - m*c[i - 1];	// Recalculate the main diagonal vector
		d[i] = d[i] - m*d[i - 1];	// Recalculate the solution vector at time step k
	}

	// Compute xn

	x[N - 1] = d[N - 1] / b[N - 1];	// using d and b

	// Loop for the backward substitution phase

	for (int i = N - 2; i >= 0; i--)
	{
		x[i] = (d[i] - c[i] * x[i + 1]) / b[i];	// Calculate the solution vector at time step k+1
	}
	return x;
}

// TriMatrix class destructor

TriMatrix::~TriMatrix() {}