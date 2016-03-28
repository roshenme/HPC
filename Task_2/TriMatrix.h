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
	vector<double> MainDiag;		// The main diagonal of the matrix
	vector<double> SuperDiag;		// The super diagonal of the matrix
	vector<double> SubDiag;			// The sub diagonal of the matrix
public:
	TriMatrix();							// Constructor
	void set_A(vector<double>, vector<double>, vector<double>);		// To set the values of the matrix
	vector<double> get_U(vector<double>);	// To get the values of U after matrix-vector multiplication
	~TriMatrix();							// Destructor
};