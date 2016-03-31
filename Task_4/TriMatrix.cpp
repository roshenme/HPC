////////////////////////////////////////////
////// TriMatrix Class Implementation //////
////////////////////////////////////////////

#include<iostream>
#include<vector>
#include "TriMatrix.h"	// Include the class header file

using namespace std;

// Matrix Vector Multiplication BLAS

extern "C" void dgbmv_(const char& TRANS, const int *m, const int *n, int *kl, int *ku,
	double *alpha, const double *A, const int *lda, const double *x, int *incx, double *beta, double *y,
	int *incy);

// Matrix Vector solve LAPACK

extern "C" void dgtsv_(const int *N, const int *nrhs, double *dl, double *d, double *du,
	double *b, const int *ldb, int *info);

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

	// Store A in row major form

	A.resize(3 * N);

	for (int i = 0; i < N - 1; i++)
	{
		A[3 * (i + 1)] = SubDiagA[i];
		A[3 * i + 1] = MainDiagA[i];
		A[3 * i + 2] = SuperDiagA[i];
	}

	A[3 * N - 2] = MainDiagA[N - 1];
}

// Set the coefficient matrix B

void TriMatrix::set_B(vector<double> UpperB, vector<double> MainB, vector<double> LowerB)
{
	int N = UpperB.size();			// Define size N
	SuperDiagB.resize(N);			// Set the size of the super diagonal to N
	SuperDiagB = UpperB;
	MainDiagA.resize(N + 1);		// Set the size of the main diagonal to N+1
	MainDiagB = MainB;
	SubDiagB.resize(N);				// Set the size of the sub diagonal to N
	SubDiagB = LowerB;
}

// Implement matrix-vector multiplicaton to get the temperature vector

vector<double> TriMatrix::get_U(vector<double> u)
{
	int n = u.size();				// Assign the size of U as variable N

	// Provide the inputs for the BLAS function dgbmv

	int M = n;			// Number of columns of the matrix A
	int N = n;			// Number of rows of the matrix A
	int kl = 1;			// Number of sub diagonals of matrix A
	int ku = 1;			// Number of super diagonals of matrix A
	double alpha = 1.0;	// Scalar provided get the equation in y=Au form
	double beta = 0.0;	// Scalar provide to get the equation in y=Au form
	int lda = 3;		// First dimension of A (kl+ku+1)
	int incx = 1;		// Increment for the elements of u				
	int incy = 1;		// Increment for the elements of y

	vector<double> y(n, 1);			// Initialise the solution

	// Implement the function dgbmv

	dgbmv_('T', &M, &n, &kl, &ku, &alpha, &A[0], &lda, &u[0], &incx, &beta, &y[0], &incy);

	return y;						// Return the matrix vector mutiplied product vector y
}

// The Thomas Algorithm to solve the matrix equation

vector<double> TriMatrix::MatVecSolve(vector<double> U)
{
	int N = U.size();				// Define the size of the input vector from main (Order of matrix A)
	int nrhs = 1;					// Number of columns of the RHS matrix (1=vector)
	int ldb = N;					// Leading dimension of array B (Vector)
	int info;

	vector<double> dl = SubDiagB;	// Sub diagonal input to dgtsv
	dl.push_back(0);				// Remove the first element from the sub diagonal

	vector<double> d = MainDiagB;	// Main diagonal input to dgtsv

	vector<double> du = SuperDiagB;	// Super diagonal input to dgtsv
	du.push_back(N);				// Remove the last element from the super diagonal

	// Implement the function dgtsv

	dgtsv_(&N, &nrhs, &dl[0], &d[0], &du[0], &U[0], &ldb, &info);

	return U;						// Return the solution U
}

// TriMatrix class destructor

TriMatrix::~TriMatrix() {}
