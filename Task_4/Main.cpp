////////////////////////////////////////////
//// AE3-422 High_Performance Computing ////
////////////////////////////////////////////
////  By Roshendra Suroshan Abewickrama ////
////////////////////////////////////////////

// To include in this code

#include<iostream>
#include<vector>
#include "TriMatrix.h"
#include <ctime>


using namespace std;

// Start of the Main program

int main()
{
	clock_t start;						// Start the timer
	start = clock();

	float L, Nx, T, Nt, a, theta;		// Declare L, Nx, T, Nt, a as floating point numbers 

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

	vector<float> U_O(Nx + 1);				// Initialise the intial conditions vector
	U_O[0] = 0;								// Boundary condition when x=0
	U_O[Nx] = 0;							// Boundary condition when x=L
	for (int i = 1; i < Nx; i++)			// Start the loop to go through all the nodes
	{
		U_O[i] = x[i] * (1 - x[i]);				// Calculate and assign the temperature at each node using the given function
		//U_O[i] = sin((22 / 7)*x[i] / L);	// Calculate and assign the temperature at each node using the given function
		cout << U_O[i] << " ";				// Output intial conditions vector
	}
	cout << endl << endl;

	// Prompt user to choose which scheme the user wants use to solve the system
	// The Forward Euler, Backward Euler or the Crank-Nicolson Schemes

	char cont = 'y';

	while (cont == 'y')
	{
		cout << "Enter value for theta" << endl << "0 for the Forward Euler Scheme " << endl << "1 for the Backward Euler Scheme " << endl << "0.5 for the Crank-Nicolson Scheme ";
		cin >> theta;
		while (theta != 0.0 && theta != 0.5 && theta != 1.0)
		{
			cout << "Theta has to be 0,1 or 0.5. Please enter the value again!";
			cin >> theta;
		}

		// Initialise the diagonals of A

		vector<double> MainDiagA(Nx + 1);	// Initialize the main diagonal
		vector<double> SubDiagA(Nx);		// Initialize the sub diagonal
		vector<double> SuperDiagA(Nx);		// Initialize the super diagonal

		// Set the coefficient matrix A using the TriMatrix Class

		MainDiagA[0] = 1;									// The first value of the main diagonal is 1
		MainDiagA[Nx] = 1;									// The last value of the main diagonal is 1
		MainDiagA[Nx - 1] = 1 + ((1 - theta)*v*(-2));		// The second last value of the main diagonal is 1-2v

		SubDiagA[0] = (1 - theta)*v;		// The first value of the sub diagonal is v
		SubDiagA[Nx - 1] = 0;				// The last value of the sub diagonal is 0

		SuperDiagA[0] = 0;					// The first value of the sub diagonal is 0
		SuperDiagA[Nx - 1] = (1 - theta)*v;	// The last value of the sub diagonal is v

		for (int i = 1; i < Nx - 1; i++)
		{
			MainDiagA[i] = 1 + ((1 - theta)*v*(-2));	// Fill in the rest of the values of the main diagonal with 1-2v
			SubDiagA[i] = (1 - theta)*v;				// Fill in the rest of the values of the sub diagonal with v
			SuperDiagA[i] = (1 - theta)*v;				// Fill in the rest of the values of the superdiagonal with v
		}

		// Instantiate and populate the TriMatrix class

		TriMatrix Tri;									// Instantiate the class
		Tri.set_A(SuperDiagA, MainDiagA, SubDiagA);		// Populate the the TriMatrix class

		// Initialise the diagonals of B

		vector<double> MainDiagB(Nx + 1);	// Initialize the main diagonal
		vector<double> SubDiagB(Nx);		// Initialize the sub diagonal
		vector<double> SuperDiagB(Nx);		// Initialize the super diagonal

		// Set the coefficient matrix B using the TriMatrix Class

		MainDiagB[0] = 1;									// The first value of the main diagonal is 1
		MainDiagB[Nx] = 1;									// The last value of the main diagonal is 1
		MainDiagB[Nx - 1] = 1 - (theta*v*(-2));				// The second last value of the main diagonal is 1-2v

		SubDiagB[0] = -theta*v;				// The first value of the sub diagonal is v
		SubDiagB[Nx - 1] = 0;				// The last value of the sub diagonal is 0

		SuperDiagB[0] = 0;					// The first value of the sub diagonal is 0
		SuperDiagB[Nx - 1] = -theta*v;		// The last value of the sub diagonal is v

		for (int i = 1; i < Nx - 1; i++)
		{
			MainDiagB[i] = 1 - (theta*v*(-2));		// Fill in the rest of the values of the main diagonal with 1-2v
			SubDiagB[i] = -theta*v;					// Fill in the rest of the values of the sub diagonal with v
			SuperDiagB[i] = -theta*v;				// Fill in the rest of the values of the superdiagonal with v
		}

		// Populate the TriMatrix class

		Tri.set_B(SuperDiagB, MainDiagB, SubDiagB);		// Populate the the TriMatrix class

		// Initialise the solution vectors

		vector<double> Un(Nx + 1);			// Initialize Un
		vector<double> U(Nx + 1);			// Initialise U
		vector<double> UL(Nt + 1);			// Initialise UL to store the L/2 values at all time steps

		// Choose the scheme depending on the user input to theta

		if (theta == 0.0)
		{
			cout << endl << "Forward Euler scheme" << endl;

			// The time iteration loop

			for (int i = 0; i < Nx + 1; i++)
			{
				U[i] = U_O[i];				// Set the U of the first iteration as initial vector
			}

			for (int i = 0; i <= Nt; i++)
			{
				Un = Tri.get_U(U);			// Class implementation
				U = Un;						// Form U for the next iteration
				UL[i] = U[(Nx / 2) + 1];	// Store the temperature at L/2 at each time step
			}
		}
		else if (theta == 1.0)
		{
			cout << endl << "Backward Euler" << endl;

			// The time iteration loop

			for (int i = 0; i < Nx + 1; i++)
			{
				U[i] = U_O[i];				// Set the U of the first iteration as initial vector
			}

			for (int i = 0; i <= Nt; i++)
			{
				Un = Tri.MatVecSolve(U);
				U = Un;
				UL[i] = U[(Nx / 2) + 1];
			}
		}
		else
		{
			cout << endl << "Crank-Nicolson" << endl;

			// The time iteration loop

			for (int i = 0; i < Nx + 1; i++)
			{
				U[i] = U_O[i];				// Set the U of the first iteration as initial vector
			}

			for (int i = 0; i <= Nt; i++)
			{
				Un = Tri.get_U(U);            //Forward Euler
				U = Tri.MatVecSolve(Un);        //Backward Euler
				UL[i] = U[(Nx / 2) + 1];
			}
		}

		// Display the final temperature vector

		cout << "The final temperature vector" << endl << endl;		// Print on output screen

		for (int i = 0; i < Nx + 1; i++)
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
		
		// Calculate the time to run the program

		float dttt = (clock() - start) / (double)CLOCKS_PER_SEC;
		cout << endl << endl << endl << "Time taken to run the program (s)" << endl << endl;		// Print on output screen
		cout <<dttt << endl << endl;

		// Ask the user whether he/she would like to continue and use the same/different scheme 

		cout << endl << "Would you like to continue? (y = Yes, n = No) ";
		cin >> cont;
		cout << endl << endl;
	}

	system("pause");

	return 0;
}
