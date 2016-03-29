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
	int M = n;
	int N = n;
	int kl = 1;
	int ku = 1;
	double alpha = 1.0;
	double beta = 0.0;
	int lda = 3;
	int incx = 1;
	int incy = 1;

	vector<double> y(n, 1);

	dgbmv_('T', &M, &n, &kl, &ku, &alpha, &A[0], &lda, &u[0], &incx, &beta, &y[0], &incy);
	return y;
}

// Operator overloading to overload the forward slash operator

vector<double> TriMatrix::MatVecSolve(vector<double> U)
{
	int N = U.size();				// Define the size of the input vector from main
	int nrhs = 1;
	int ldb = N;
	int info;

	vector<double> dl = SubDiagB;
	dl.pop_back();

	vector<double> d = MainDiagB;

	vector<double> du = SuperDiagB;
	dl.pop_back();

	dgtsv_(&N, &nrhs, &dl[0], &d[0], &du[0], &U[0], &ldb, &info);

	return U;
}

// TriMatrix class destructor

TriMatrix::~TriMatrix() {}
