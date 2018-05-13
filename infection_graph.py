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

mostinfected = np.asarray([0,0,0,0,0,0,0,0,0,0])

for i in range(0,5000):
    #reset infection chart to 0
    infectedmax = []
    for i in range(0,10):

        #reset population.
        pop = Population(100, random.randint(1,100))
        pop.set_probability_of_transfer(i/10.0)
        pop.set_contact_count(6)
        pop.set_days_sick(5)
        pop.set_vaccinated(0);
        pop.vaccinate();
        pop.random_infection();
        day = []
        inf = []
        sus = []
        rec = []
        vac = []

        #run simulation.
        while(pop.count_infected()!=0):
            day.append(pop.current_day())
            inf.append(pop.count_infected())
            sus.append(pop.count_susceptible())
            rec.append(pop.count_recovered())
            vac.append(pop.count_vaccinated())
            pop.update()
        #updated for last day where infected==0.
        day.append(pop.current_day())
        inf.append(pop.count_infected())
        sus.append(pop.count_susceptible())
        rec.append(pop.count_recovered())
        vac.append(pop.count_vaccinated())
        #simulation ends

        #get peak of infection.
        infectedmax.append(max(inf))
    #turn into array and add to average, mostinfected.
    infectedmax = np.asarray(infectedmax)
    mostinfected+=infectedmax

mostinfected =  mostinfected/5000.0




inf = np.asarray(inf)
day = np.asarray(day)
rec = np.asarray(rec)


plt.xlabel('probability of infection')
plt.ylabel('peak infection count')

x = np.arange(0.,1.,.1)
plt.plot(x, np.poly1d(np.polyfit(x,mostinfected,4))(x))
plt.plot(x,mostinfected, 'ro')

plt.show()
