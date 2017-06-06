import numpy as np
from random import *

Nsites = 4
Nitr = 5000

#Create a normalized spin
def normSpin():
    vec = [random() for i in range(3)]
    return vec/np.sqrt(vec[0]**2 + vec[1]**2 + vec[2]**2)

#Create spin configuration
def createRandomConfig():
    return [normSpin() for i in range(Nsites)]

#Define ferromagnetic exchange matrix
def exchangeMatrix():
    return [[-1 for i in range(Nsites)] for j in range(Nsites)]

#Choose a random spin index
def chooseRandomIndex():
    return randint(0,Nsites-1)

#Return random spin
def chooseRandomSpin(spins, index):
    return spins[index]

#Calculate the change in energy when flipping a spin
def energyChange(jij, oldspin, newspin, index, spins):
    deltaEnergy = 0
    for i in range(index):
        deltaEnergy += 2*jij[index][i]*np.dot(newspin-oldspin, spins[i])
    for i in range(index+1, Nsites):
        deltaEnergy += 2*jij[index][i]*np.dot(newspin-oldspin, spins[i])
    return deltaEnergy

#Calculate energy
def calculateEnergy(jij,spins):
    energy = 0
    for i in range(Nsites):
        for j in range(Nsites):
            energy += jij[i][j]*np.dot(spins[i], spins[j])
    return energy


def decideSpinFlip(jij, oldspin, newspin, index, spins):
    if energyChange(jij, oldspin, newspin, index, spins) < 0:
        spins[index] = newspin

# MC algorithm
# 1) Random config
# 2) Define J_ij
# 3) Pick random site
# 4) Consider random spin
# 5) Calculate energy change
# 6) Accept or reject
# 7) Repeat

def monteCarlo():
    config = createRandomConfig()
    jij = exchangeMatrix()
    for i in range(Nitr):
        itr = chooseRandomIndex()
        old = chooseRandomSpin(config, itr)
        new = normSpin()
        decideSpinFlip(jij, old, new, itr, config)
    print "The spin configuration resulting from Monte Carlo is " + str(config)
    print "The energy of the spin configuration is " + str(calculateEnergy(jij,config))

monteCarlo()
print "The exact energy of this system is " + str(-Nsites**2)