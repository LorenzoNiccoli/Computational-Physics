# This script resolves the Lotka-Volterra equation, also known as the pray-predator model.
# Like in the classical description it is assumed that the pray (e.g. rabbits) and the 
# predator (e.g. foxes) are only species in the ecosistem. The predator has a negative impact
# on pray population while the pray has a positive impact on predator population.
# The Newton equation of motion are solved using the standard Verlet algorithm
# 
# Parameters:
#     pray_t0			    -	    initial pray population
#	    predator_t0		  -	    initial predator population
#	    a				        -	    pray natural grow rate
#	    b				        - 	  pray death rate due to predators
#	    c				        - 	  predator natural death rate	
#	    d				        -	    number of eaten pray to give a new predator
#	    timestep		    -	    timestep of the simulation
#	    end_time		    -  	  lenght of the simulation 
#
# Outputs:
#	    pray			  -    pray population variation over time
#	    predator    -	   predator population variation over time
#
# Note:
# 	  1.	A stationaty solution is obatined if pray_t0 = a/b and predator_t0 = c/d. 
#
# Author: Lorenzo Niccoli
# Email:  lorenzo.niccol@unifi.it

import matplotlib.pyplot as plt
import numpy as np

pray_t0 = 10
predator_t0 = 10
a = 1
b = 0.1
c = 1
d = 1
timestep = 0.01
end_time = 100

# Time vector
t = np.arange(0,end_time,timestep)

# Intialize rabbits (x) and foxes (y) vectors
pray = []
predator = []

# Initial conditions for pray and predator populations at time=0
pray.append(pray_t0)
predator.append(predator_t0)

# Integration: Euler method
for index in range(1,len(t)):
    # Evaluate the current differentials: eq. definition
    xd = pray[index-1] * (a - b*predator[index-1])
    yd = -predator[index-1]*(c - d*pray[index-1])
    
    # Evaluate the next value of pray and predator 
    next_x = pray[index-1] + xd * timestep
    next_y = predator[index-1] + yd * timestep

    # Build the pray and population vectors 
    pray.append(next_x)
    predator.append(next_y)

" Plots "
fig, (ax1,ax2) = plt.subplots(1,2 , constrained_layout=True)
# Population against time
ax1.plot(t, pray)
ax1.plot(t, predator)
ax1.set_xlabel('Time')
ax1.set_ylabel('Population Size')
ax1.set_title('Deterministic Lotka-Volterra')
ax1.legend(('Rabbits', 'Foxes'))
ax1.grid()

# Phase portrait
ax2.plot(pray,predator)
ax2.set_xlabel('Fox Population')
ax2.set_ylabel('Rabbit Population')
ax2.set_title('Phase Portrait of Deterministic Lotka-Volterra')
ax2.grid()

plt.show()


# "The Calculus required continuity, and continuity was supposed to require the 
# infinitely little; but nobody could discover what the infinitely little might be."
# Bertrand Russell
