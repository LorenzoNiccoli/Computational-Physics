# Armonic oscillator: symplectic and non-symplectic Euler map
# 
# Parameters:
#     x       -   starting position             [m]
#     p       -   starting momentum             [m/s]
#     w       -   frequency of the oscillation  [1/s]
#     dt      -   time step                     [s]
#     Nsteps  -   number of steps
#
# Outputs:
#     xv_notConserved     -    position over time, non-symplectic map 	[m]
#     pv_notConserved     -    momenta over time, non-symplectic map   	[m/s]
#     xv_Conserved     	  -    position over time, symplectic map 	[m]
#     pv_Conserved    	  -    momenta over time, symplectic map   	[m/s]
#
# Notes: 
#	  1. This is a very basic code that shows the differences between a volume
#		   preserved and a non-volume preserved solution of an harmonic oscillator.
#		   It serves as a tutorial and it is not the most efficient solution. 
#
# Author : Lorenzo Niccoli
# Email  : lorenzo.niccoli@unifi.it (March 2023)

import numpy as np
import matplotlib.pyplot as plt


# Initial conditions :
N_steps = 100
w  = 1
dt = 0.1
x,p = np.random.random(2)


# Functions definition:
# Non-symplectic Euler map, non-conserved volume
def map_noncons(x,p):
	xn,pn = x + p*dt, p - w**2*x*dt
	return xn,pn

# Symplectic Euler map, conserved volume
def map_cons(x,p):
	xn = x + p*dt
	p1n = p
	xn1 = xn
	pn1 = p - w**2*xn*dt
	return xn1,pn1	

# Outputs calculation: 
xv_notConserved = []
pv_notConserved = []
for n in range(N_steps):
	xn,pn = map_noncons(x,p)
	x,p = xn,pn
	xv_notConserved.append(x)
	pv_notConserved.append(p)

xv_Conserved = []
pv_Conserved = []
for n in range(N_steps):
	xn,pn = map_cons(x,p)
	x,p = xn,pn
	xv_Conserved.append(x)
	pv_Conserved.append(p)

  
# Plot
fig, (ax1,ax2) = plt.subplots(1,2 , constrained_layout=True)
# Plot 1: symplectic
ax1.plot(xv_notConserved,pv_notConserved, linewidth =1)
ax1.set_xlabel('Position', size=13)
ax1.set_ylabel('Momenta', size=13)
ax1.set_title('Non-Symplectic map', size =16)
ax1.grid()
# Plot 2: symplectic
ax2.plot(xv_Conserved,pv_Conserved, linewidth =1)
ax2.set_xlabel('Position', size=13)
ax2.set_ylabel('Momenta', size=13)
ax2.set_title('Symplectic map', size =16)
ax2.grid()
# Plot options:
plt.show()



 
# "Science is a differential equation. Religion is a boundary condition"
# Alan Turing, epigram to Robin Gandy (1954)
