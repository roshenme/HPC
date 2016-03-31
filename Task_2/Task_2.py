############################################
##### Analytical vs Numerical Solution #####
############################################

# Import the libraries to run the C++ program and to plot the graphs

import subprocess 
import matplotlib.pyplot as mp
import numpy as np

# Provide variables as the arguments to the script in string format

L=1           # Length of the domain
Nx=20         # Number of nodes  
T=1           # Final time
Nt=1000       # Number of time steps
a=1           # Thermal Coefficient

# Convert the variables to strings

L=str(L)
Nx=str(Nx)
T=str(T)
Nt=str(Nt)
a=str(a)

# Use the subspace module
subprocess.call(["Main.exe",L,Nx,T,Nt,a],shell=True)

file=open("Temperaturehalf.txt","r")                # Open the .txt file with all the temperatures
t1,Numerical_Sol1 = np.loadtxt(file,unpack=True)    # Read the values and assign to Temp
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
Analytical_Sol1=[]

for i in t:
    An_Sol=np.sin(np.pi*x_mid/L)*np.exp(-i*a*(np.pi/L)**2)
    Analytical_Sol1.append(An_Sol)

# Form the final Analytical solution in the loop

mp.plot(t1, Analytical_Sol1,label="Analytical Solution")                    # Plot the Analytical Solution
mp.title('Temperature decay for the Analytical and Numerical Solutions')    # Title of plot
mp.xlabel('Time')                                                           # Label x-axis
mp.ylabel('Temperature')                                                    # Label y-axis
mp.plot(t, Numerical_Sol1,label="Numerical Solution")                       # Plot the Numerical Solution
mp.legend(loc=1)                                                            # Add legend to the graph
mp.show()                                                                   # Show the graph

# Compute the error between the analytical and numerical solutions

Err1=Analytical_Sol1-Numerical_Sol1

# The Analytical and Numerical Solutions can be compared

mp.plot(t, Err1)                                                # Plot the Analytical Solution
mp.title('Error between Analytical and Numerical Solutions')    # Title of plot
mp.xlabel('Time')                                               # Label x-axis
mp.ylabel('Temperature Error')                                  # Label y-axis
mp.legend(loc=2)                                                # Add legend to the graph
mp.show()                                                       # Show the graph

#############################################################################
#############################################################################
#############################################################################

# Run the program at different Nx values

# Provide the Nx values as strings

Nxx=["4","5","8","10","16","20"]

# Start the loop for the different values of Nx
RMSx=[]             # Initialise empty array to store RMS value
dxx=[]              # Initialise empty array to store different dx value corresponding to the different Nx value
for i in Nxx:       # Start the loop to go through the provided values of Nx

    # Convert the arguments to string 

    L=str(L)  
    T=str(T)   
    Nt=str(Nt)  
    a=str(a)    

    subprocess.call(["Main.exe",L,i,T,Nt,a])         # Use the subspace module

    file=open("Temperature.txt","r")                 # Open the .txt file with all the temperatures
    Numerical_Sol2= np.loadtxt(file,unpack=True)     # Read the values and assign to Temp vector
    file.close()                                     # Close the file

    # Convert the strings into floating point numbers

    L=float(L)
    Nxnew=float(i)
    T=float(T)
    Nt=float(Nt)
    a=float(a)

    # Generate the values of x for the current Nx in the loop

    X=np.arange(0,L+L/Nxnew,L/Nxnew)

    # Do a loop to calculate the analytical solution at all the nodes for the current Nx

    U_Analytical=0              # Initialise the analytical solution as zero
    Analytical_Sol2=[]           # Initialise an empty array to store the analytical solutions
    for j in X:
        U_Analytical=np.sin(np.pi*(j/L))*np.exp(-T*a*(np.pi/L)**2) 
        Analytical_Sol2.append(U_Analytical)

    # Calculate the error between the Analytical and Numerical solutions

    Err2=Numerical_Sol2-Analytical_Sol2

    # Create the vector with the different dx values

    dx=L/Nxnew
    dxx.append(dx)

    # Calculate the RMS error for the current vector
    
    RMS=np.sqrt(np.mean(np.square(Err2)))

    # Assemble the value to RMSx which will store the RMS error for different Nx values

    RMSx.append(RMS)

# Plot RMSx against the dx values

mp.plot(dxx, RMSx,'ro')                                                     # Plot the Analytical Solution
mp.title('RMS Error of the solution for different mesh sizes dx')           # Title of plot
mp.xlabel('dx')                                                             # Label x-axis
mp.ylabel('RMS Error')                                                      # Label y-axis
mp.legend(loc=2)                                                            # Add legend to the graph
mp.show()

#############################################################################
#############################################################################
#############################################################################

# Run the program at different Nt values

# Provide the Nt values as strings

Ntt=["800","1000","1100","1200"]
    
# Start the loop for the different values of Nt
RMSt=[]             # Initialise empty array to store RMS value
dtt=[]              # Initialise empty array to store different dx value corresponding to the different Nx value
for i in Ntt:       # Start the loop to go through the provided values of Nx

    # Convert the arguments to string 

    L=str(L)  
    Nx=str(Nx)  
    T=str(T)   
    a=str(a)    

    subprocess.call(["Main.exe",L,Nx,T,i,a])         # Use the subspace module

    file=open("Temperaturehalf.txt","r")             # Open the .txt file with all the temperatures
    t3,Numerical_Sol3= np.loadtxt(file,unpack=True)  # Read the values and assign to Temp vector
    file.close()                                     # Close the file

    # Convert the strings into floating point numbers

    L=float(L)
    Nx=float(Nx)
    T=float(T)
    Ntnew=float(i)
    a=float(a)
    x_mid=L/2       # Define the mid point of the domain

    # Generate the values of x for the current Nx in the loop

    tnew=np.arange(0,T+T/Ntnew,T/Ntnew)
    
    # Do a loop to calculate the analytical solution at all the nodes for the current Nx

    U_Analytical=0              # Initialise the analytical solution as zero
    Analytical_Sol3=[]           # Initialise an empty array to store the analytical solutions
    for j in tnew:
        U_Analytical=np.sin(np.pi*(x_mid/L))*np.exp(-j*a*(np.pi/L)**2) 
        Analytical_Sol3.append(U_Analytical)

    # Calculate the error between the Analytical and Numerical solutions

    Err3=Numerical_Sol3-Analytical_Sol3

    # Create the vector with the different dx values

    dt=T/Ntnew
    dtt.append(dt)

    # Calculate the RMS error for the current vector
    
    RMSnew=np.sqrt(np.mean(np.square(Err3)))

    # Assemble the value to RMSx which will store the RMS error for different Nx values

    RMSt.append(RMSnew)

# Plot RMSx against the dx values

mp.plot(dtt, RMSt,'ro')                                                     # Plot the Analytical Solution
mp.title('RMS Error of the solution for different time step sizes')         # Title of plot
mp.xlabel('dt')                                                             # Label x-axis
mp.ylabel('RMS Error')                                                      # Label y-axis
mp.legend(loc=2)                                                            # Add legend to the graph
mp.show()