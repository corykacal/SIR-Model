from pylib_auto import Population
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt
import numpy as np

pop = Population(100,0)
pop.set_probability_of_transfer(.3)
pop.set_contact_count(6)
pop.set_days_sick(5)
pop.set_vaccinated(0);
pop.vaccinate();

pop.random_infection();

day = []
infected = []
sus = []
rec = []
vac = []

while(pop.count_infected()!=0):
    day.append(pop.current_day())
    infected.append(pop.count_infected())
    sus.append(pop.count_susceptible())
    rec.append(pop.count_recovered())
    vac.append(pop.count_vaccinated())
    pop.update()

day.append(pop.current_day())
infected.append(pop.count_infected())
sus.append(pop.count_susceptible())
rec.append(pop.count_recovered())
vac.append(pop.count_vaccinated())


plt.plot(day,infected, 'r')
plt.plot(day,sus, 'c')
plt.plot(day,rec, 'b')
plt.plot(day,vac, 'g')

inf = mpatches.Patch(color='r', label='infected count')
sus = mpatches.Patch(color='c', label='susceptible count')
vac = mpatches.Patch(color='g', label='vaccinated count')
rec = mpatches.Patch(color='b', label='recovered count')

plt.legend(bbox_to_anchor=(0,1.02,1,.102),handles=[inf,sus,vac,rec],loc=1,ncol=2,borderaxespad=0)
plt.show()
