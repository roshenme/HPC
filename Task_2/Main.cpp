////////////////////////////////////////////
//// AE3-422 High_Performance Computing ////
////////////////////////////////////////////
////  By Roshendra Suroshan Abewickrama ////
////////////////////////////////////////////

// To include in this code

#include<iostream>
#include<vector>
#include "TriMatrix.h"
#include<fstream>

using namespace std;

// Start of the Main program

int main(int args, char** argv)
{
	float L, Nx, T, Nt, a;		// Declare L, Nx, T, Nt, a as floating point numbers 

	// Variables are to be provided as arguments in the python program

	L = atof(argv[1]);
	Nx = atof(argv[2]);
	T = atof(argv[3]);
	Nt = atof(argv[4]);
	a = atof(argv[5]);

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
	vector<double> UL(Nt + 1);		// Initialise UL to store the L/2 values at all time steps

	for (int i = 0; i<Nx + 1; i++)
	{
		U[i] = U_O[i];				// Set the U of the first iteration as initial vector
	}

	for (int i = 0; i <= Nt; i++)
	{
		Un = Tri.get_U(U);			// Class implementation
		U = Un;						// Form U for the next iteration
		UL[i] = U[Nx / 2 + 1];		// Store the temperature at L/2 at each time step
	}

	// Display the final temperature vector

	cout << "The final temperature vector" << endl << endl;		// Print on output screen

	for (int i = 0; i<Nx + 1; i++)
	{
		cout << U[i] << " ";		// Output the final temperature vector
	}
	cout << endl << endl;

	// Display the temperature at L/2 at all the time steps

	cout << "The temperature at L/2 at all the time steps" << endl << endl;		// Print on output screen

	for (int i = 0; i <= Nt; i++)
	{
		cout << UL[i] << " ";		// Output the temperature at L/2 at all time steps in vector form
	}

	// Write the time vector and UL vector into a .txt file to be used by python

	ofstream file;
	file.open("Temperaturehalf.txt");	// Open the file

	for (int i = 0; i < Nt+1; i++)
	{
		file << i*dt << "\t" << UL[i] << endl;	// Write the time and temperature of L/2 at each time step
	}

	file.close();	// Close the file

	// Write the U vector into a .txt file to be used by python

	file.open("Temperature.txt");		// Open the file

	for (int i = 0; i < Nx+1; i++)
	{
		file << U[i] << endl;			// Write one value at a time in a loop
	}

	file.close();	// Close the file

	system("pause");

	return 0;
}
