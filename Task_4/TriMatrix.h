////////////////////////////////////////////
///////////// TriMatrix Class //////////////
////////////////////////////////////////////

#pragma once
#include<iostream>
#include<vector>

using namespace std;

class TriMatrix						// Start the class
{
private:							// Define the private member functions
	vector<double> MainDiagA;		// The main diagonal of the matrix A
	vector<double> SuperDiagA;		// The super diagonal of the matrix A
	vector<double> SubDiagA;		// The sub diagonal of the matrix A
	vector<double> MainDiagB;		// The main diagonal of the matrix B
	vector<double> SuperDiagB;		// The super diagonal of the matrix B
	vector<double> SubDiagB;		// The sub diagonal of the matrix B
	vector<double> A;				// Matrix A to be input	
public:
	TriMatrix();								// Constructor
	void set_A(vector<double>, vector<double>, vector<double>);		// To set the values of the matrix A
	void set_B(vector<double>, vector<double>, vector<double>);		// To set the values of the matrix B
	vector<double> MatVecSolve(vector<double>);	// Solve the matrix equation
	vector<double> get_U(vector<double>);		// To get the values of U after matrix-vector multiplication
	~TriMatrix();								// Destructor
};