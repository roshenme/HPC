############################################
##### Analytical vs Numerical Solution #####
############################################

# Import the libraries to run the C++ program and to plot the graphs

import subprocess 
import matplotlib.pyplot as mp
import numpy as np

# Provide variables as the arguments to the script in string format

L="1"           # Length of the domain
Nx="20"         # Number of nodes  
T="1"           # Final time
Nt="1000"       # Number of time steps
a="1"           # Thermal Coefficient

# Use the subspace module
subprocess.call(["Main.exe",L,Nx,T,Nt,a],shell=True)

file=open("Temperaturehalf.txt","r")                # Open the .txt file with all the temperatures
ti,Numerical_Sol = np.loadtxt(file,unpack=True)          # Read the values and assign to Temp
file.close()                                        # Close the file

# Convert the strings into floating point numbers

L=float(L)
Nx=float(Nx)
T=float(T)
Nt=float(Nt)
a=float(a)
x_mid=L/2       # Define the mid point of the domain

# Start the loop to calculate the Analytical solution using the given sin function

t=np.arange(0,T+T/Nt,T/Nt)
An_Sol=0
Analytical_Sol=[]

for i in t:
    An_Sol=np.sin(np.pi*x_mid/L)*np.exp(-i*a*(np.pi/L)**2)
    Analytical_Sol.append(An_Sol)

# Form the final Analytical solution in the loop

mp.plot(ti, Analytical_Sol,label="Analytical Solution")                     # Plot the Analytical Solution
mp.title('Temperature decay for the Analytical and Numerical Solutions')    # Title of plot
mp.xlabel('Time')                                                           # Label x-axis
mp.ylabel('Temperature')                                                    # Label y-axis
mp.plot(t, Numerical_Sol,label="Numerical Solution")                        # Plot the Numerical Solution
mp.legend(loc=1)                                                            # Add legend to the graph
mp.show()                                                                   # Show the graph

# Compute the error between the analytical and numerical solutions

Err=Analytical_Sol-Numerical_Sol

# The Analytical and Numerical Solutions can be compared

mp.plot(t, Err)                                                 # Plot the Analytical Solution
mp.title('Error between Analytical and Numerical Solutions')    # Title of plot
mp.xlabel('Time')                                               # Label x-axis
mp.ylabel('Temperature Error')                                  # Label y-axis
mp.legend(loc=2)                                                # Add legend to the graph
mp.show()                                                       # Show the graph

#############################################################################
#############################################################################
#############################################################################
