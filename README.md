# Monte-Carlo-Ferromagnetic-Ground-State
Code that calculates the ground state of a ferromagnetic exchange matrix. Codes in C++ (STL), Python, and Matlab

The code first generates a configuration of Nsites random normalized spins. The code then generates what is known as an exchange matrix. It describes the interaction energies between the spins. The exchange matrix has exactly the same interaction energy(-1) between all pairs of spins. In such a system, the way to minimize the energy is to have all of the spins point in the same direction. Monte Carlo is a technique we can use to find this optimal state of the system. Monte Carlo is a brute force numerical technique.

Our Monte Carlo algorithm here consists of the following steps:
1) Choose a random spin configuration with Nsites spins
2) Generate an Nsites x Nsites matrix with all elements set to -1
3) In a for loop of Nitr iterations,
4) Choose one of the spins in the configuration randomly
5) Generate a new random spin
6) Compare the energy of the system with the new spin. If it is lowered with the new spin, keep the new spin in the configuration. If it is not lowered, reject the new spin and keep the old spin.
7) Once the for loop is done, check the energy of the system and compare it to the analytic solution.
