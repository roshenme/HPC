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
#include<iomanip>

using namespace std;

// Start of the Main program

int main(int args, char** argv)
{					
	float L, Nx, T, Nt, a;			// Declare the variables

	// To be provided in the python file as arguments

	L = atoi(argv[1]);
	Nx = atoi(argv[2]);
	T = atoi(argv[3]);
	Nt = atoi(argv[4]);
	a = atof(argv[5]);

	// Calculate dx, dt and v

	float dx = float(L) / float(Nx);			// Mesh size is length of domain divided by the number of nodes
	float dt = float(T) / float(Nt);			// Time step size if final time divided by the number of time steps
	float v = (a*dt) / (dx*dx);				// Constant

	// Define the x vector with the position co-ordinates of the nodes

	cout << endl;
	cout << "The position co-ordinates vector" << endl << endl;		// Print on output screen

	vector<float> x(Nx + 1);		// Initialise the x vector
	for (int i = 0; i <= Nx; i++)		// Start the loop to go through all the nodes
	{
		x[i] = i*dx;					// Calculate and assign the x co-ordinates
		cout << x[i] << " ";			// Output the x co-ordinates vector
	}
	cout << endl << endl;				

	// Define the initial conditions vector

	cout << "The initial temperature vector" << endl << endl;	// Print on output screen

	vector<float> U_O(Nx + 1);		// Initialise the intial conditions vector
	for (int i = 0; i <= Nx; i++)		// Start the loop to go through all the nodes
	{
		U_O[i] = x[i]*(1-x[i]);			// Calculate and assign the temperature at each node using the given function
		cout << U_O[i] << " ";			// Output intial conditions vector
	}
	cout << endl << endl;

	// Set the coefficient matrix A using the TriMatrix Class

	TriMatrix Tri;			// Instantiate the class
	Tri.set_A(v, Nx);		// Populate the the Trimatrix class

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

	cout << "The temperature at L/2 at all the time steps" << endl << endl;		// Print on output screen

	for (int i = 0; i <= Nt; i++)
	{
		cout << UL[i] << " ";		// Output the temperature at L/2 at all time steps in vector form
	}

	// Write the UL vector into a .txt file to be used by python

	ofstream file;
	file.open("Temperature.txt");			// Open the file

	for (int i = 0; i < UL.size(); i++)
	{
		file << UL[i] << endl;				// Write one value at a time in a loop
	}

	file.close();	// Close the file

	system("pause");
	
	return L, Nx, T, Nt, a;
}

