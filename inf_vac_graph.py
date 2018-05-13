from pylib_auto import Population
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import time
import random



day = []
inf = []
sus = []
rec = []
vac = []

sumofall = np.zeros((100,100))

plt.ion()

fig = plt.figure(figsize=(6,3.2))
ax = fig.add_subplot(111)
plt.imshow(sumofall)
ax.set_aspect('equal')
ax.set_xlabel('initial vaccinated')
ax.set_ylabel('percent chance of infection')
plt.pause(10)

for k in range(0,100):
    mostinfected = []
    for j in range(0,100):
        #reset infection chart to 0
        infectedmax = []
        for i in range(0,100):

            #reset population.
            pop = Population(100, random.randint(1,100))
            pop.set_probability_of_transfer(j/100.0)
            pop.set_contact_count(6)
            pop.set_days_sick(5)
            pop.set_vaccinated(i);
            pop.vaccinate();
            pop.random_infection();
            inf = []

            #run simulation.
            while(pop.count_infected()!=0):
                inf.append(pop.count_infected())
                pop.update()
            #updated for last day where infected==0.
            inf.append(pop.count_infected())
            #simulation ends

            #get peak of infection.
            infectedmax.append(max(inf))
        #turn into array and add to average, mostinfected.
        mostinfected.append(infectedmax)
    mostinfected = np.asarray(mostinfected)
    sumofall+=mostinfected
    plt.imshow(sumofall)
    plt.pause(0.001)
    plt.show()


#sumofall =  sumofall/300

