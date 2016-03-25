#Provide the arguments as strings

L="1"           # Length of the domain
Nx="20"         # Number of nodes  
T="1"           # Final time
Nt="1000"       # Number of time steps
a="1"           # Thermal Coefficient

#Import the libraries to plot

import subprocess 
import matplotlib.pyplot as mp
import numpy as np

# Plot the L/2 solution over time

# Use the subspace module
lines=subprocess.call(["Main.exe",L,Nx,T,Nt,a])

file=open("Temperature.txt","r")    # Open the .txt file with all the temperatures
Temp = file.read().split('\n')      # Read the values and assign to Temp
file.close()                        # Close the file
Temp.pop()                          # Delete the last value

Numerical_Sol=[float (i.strip()) for i in Temp]

# Convert the strings into floating point numbers

L=float(L)
Nx=float(Nx)
T=float(T)
Nt=float(Nt)
a=float(a)
x_mid=0.5

#Start the loop to calculate the Analytical solution using the given sin function

t=np.arange(0,T+T/Nt,T/Nt)

def u(x,t):
    if t==0:
        return float(x*(1-x))
    else:
        val=0.0
        for i in range(1,100,2):
            val+=8.0/(np.pi**3)/(i**3)*np.sin(i*np.pi*x)*(np.e**(-(i**2)*(np.pi**2)*t)) 
            return val

# Form the final Anayltical solution in the loop

Analytical_sol=[u(x_mid,i) for i in t]

mp.plot(t, Analytical_sol,label="Analytical Solution")                      # Plot the Analytical Solution
mp.title('Temperature decay for the Analytical and Numerical Solutions')    # Title of plot
mp.xlabel('Time')                                                           # Label x-axis
mp.ylabel('Temperature')                                                    # Label y-axis
mp.plot(t, Numerical_Sol,label="Numerical Solution")                        # Plot the Numerical Solution
mp.legend(loc=1)                                                            # Add legend to the graph
mp.show()                                                                   # Show the graph