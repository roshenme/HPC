////////////////////////////////////////////
//// AE3-422 High_Performance Computing ////
////////////////////////////////////////////
////  By Roshendra Suroshan Abewickrama ////
////////////////////////////////////////////

// To include in this code

#include<iostream>
#include<vector>

using namespace std;

// Start of the Main program

int main()						
{					

	float L, T, a;				// Declare L, T and a as floating point numbers 
	int Nx, Nt;					// Declare Nx and Nt as integers 

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
		cout << "Enter the final time  ";				// Ask for T in the command window
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

	system("pause");
	
	return L, Nx, T, Nt, a;
}