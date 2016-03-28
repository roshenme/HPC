////////////////////////////////////////////
//// AE3-422 High_Performance Computing ////
////////////////////////////////////////////
////  By Roshendra Suroshan Abewickrama ////
////////////////////////////////////////////

// To include in this code

#include<iostream>
#include<vector>
#include "TriMatrix.h"

using namespace std;

// Start of the Main program

int main()
{
	float L, Nx, T, Nt, a;		// Declare L, Nx, T, Nt, a as floating point numbers 

	// Enter and Input L = The length of the domain

	do
	{
		cout << "Enter the length of the domain  ";	// Ask for L in the command window
		cin >> L;									// Assign the value to L
		if (L == 0 || cin.fail())					// Check whether the input is a number and non-zero
		{											// Otherwise display the following error message	
			cout << "Error: The length of the domain must be a number and non-zero." << endl << endl;
			cin.clear();
			cin.ignore();
		}
	} while (L == 0 || cin.fail());

	// Enter and Input Nx = The number of nodes

	do
	{
		cout << "Enter the number of nodes  ";		// Ask for Nx in the command window
		cin >> Nx;									// Assign the value to Nx
		if (Nx == 0 || cin.fail())					// Check whether the input is a number and non-zero
		{											// Otherwise display the following error message	
			cout << "Error: The number of nodes must be a number and non-zero." << endl << endl;
			cin.clear();
			cin.ignore();
		}
	} while (Nx == 0 || cin.fail());

	// Enter and Input T = The final time

	do
	{
		cout << "Enter the final time  ";			// Ask for T in the command window
		cin >> T;									// Assign the value to T
		if (T == 0 || cin.fail())					// Check whether the input is a number and non-zero
		{											// Otherwise display the following error message	
			cout << "Error: The final time must be a number and non-zero." << endl << endl;
			cin.clear();
			cin.ignore();
		}
	} while (T == 0 || cin.fail());

	// Enter and Input Nt = The number of time steps

	do
	{
		cout << "Enter the number of time steps  ";	// Ask for Nt in the command window
		cin >> Nt;									// Assign the value to Nt
		if (Nt == 0 || cin.fail())					// Check whether the input is a number and non-zero
		{											// Otherwise display the following error message	
			cout << "Error: The number of time steps must be a number and non-zero." << endl << endl;
			cin.clear();
			cin.ignore();
		}
	} while (Nt == 0 || cin.fail());

	// Enter and Input a = Thermal coefficient

	do
	{
		cout << "Enter the thermal coefficient  ";	// Ask for a in the command window
		cin >> a;									// Assign the value to Nt
		if (a == 0 || cin.fail())					// Check whether the input is a number and non-zero
		{											// Otherwise display the following error message	
			cout << "Error: The thermal coefficient must be a number and non-zero." << endl << endl;
			cin.clear();
			cin.ignore();
		}
	} while (a == 0 || cin.fail());

	// Calculate dx, dt and v

	float dx, dt, v;		// Declare the variables

	dx = L / Nx;			// Mesh size is length of domain divided by the number of nodes
	dt = T / Nt;			// Time step size if final time divided by the number of time steps
	v = (a*dt) / (dx*dx);	// Constant

	// Define the x vector with the position co-ordinates of the nodes

	cout << endl;
	cout << "The position co-ordinates vector" << endl << endl;		// Print on output screen

	vector<float> x(Nx + 1);			// Initialise the x vector
	for (int i = 0; i <= Nx; i++)		// Start the loop to go through all the nodes
	{
		x[i] = i*dx;					// Calculate and assign the x co-ordinates
		cout << x[i] << " ";			// Output the x co-ordinates vector
	}
	cout << endl << endl;

	// Define the initial conditions vector

	cout << "The initial temperature vector" << endl << endl;	// Print on output screen

	vector<float> U_O(Nx + 1);			// Initialise the intial conditions vector
	for (int i = 0; i <= Nx; i++)		// Start the loop to go through all the nodes
	{
		U_O[i] = x[i] * (1 - x[i]);		// Calculate and assign the temperature at each node using the given function
		cout << U_O[i] << " ";			// Output intial conditions vector
	}
	cout << endl << endl;

	// Set the coefficient matrix A using the TriMatrix Class

	vector<double> MainDiag(Nx + 1);	// Initialize the main diagonal
	vector<double> SubDiag(Nx);			// Initialize the sub diagonal
	vector<double> SuperDiag(Nx);		// Initialize the super diagonal

	MainDiag[0] = 1;					// The first value of the main diagonal is 1
	MainDiag[Nx] = 1;					// The last value of the main diagonal is 1
	MainDiag[Nx - 1] = 1 - 2 * v;		// The second last value of the main diagonal is 1-2v

	SubDiag[0] = v;						// The first value of the sub diagonal is v
	SubDiag[Nx - 1] = 0;				// The last value of the sub diagonal is 0

	SuperDiag[0] = 0;					// The first value of the sub diagonal is 0
	SuperDiag[Nx - 1] = v;				// The last value of the sub diagonal is v

	for (int i = 1; i < Nx - 1; i++)
	{
		MainDiag[i] = 1 - 2 * v;		// Fill in the rest of the values of the main diagonal with 1-2v
		SubDiag[i] = v;					// Fill in the rest of the values of the sub diagonal with v
		SuperDiag[i] = v;				// Fill in the rest of the values of the superdiagonal with v
	}
	
	// Instantiate and populate the TriMatrix class

	TriMatrix Tri;									// Instantiate the class
	Tri.set_A(SuperDiag, MainDiag, SubDiag);		// Populate the the TriMatrix class

	// Initialise the Un and U vectors that will form the time iteration loop

	vector<double> Un(Nx + 1);		// Initialize Un
	vector<double> U(Nx + 1);		// Initialise U

	for (int i = 0; i<Nx + 1; i++)
	{
		U[i] = U_O[i];				// Set the U of the first iteration as initial vector
	}

	for (int i = 0; i <= Nt; i++)
	{
		Un = Tri.get_U(U);			// Class implementation
		U = Un;						// Form U for the next iteration
	}

	// Display the final temperature vector

	cout << "The final temperature vector" << endl << endl;		// Print on output screen

	for (int i = 0; i<Nx + 1; i++)
	{
		cout << U[i] << " ";		// Output the final temperature vector
	}
	cout << endl << endl;

	system("pause");

	return 0;
}
