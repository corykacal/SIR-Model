#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
#include "person.cpp"
using namespace std;


class Population {

    int day;
    int size;

    int infected_cnt;
    int susceptible_cnt;
    int recovered_cnt;
    int vaccinated_cnt;

    float probability;
    int contacts;
    int sick_days;

    vector<Person*> peoples;

    public:


        /* 
         * Initializer for the population, takes in a given population count 
         */
        Population(int popcnt, int randnum) {
            size = popcnt;
            day = 0;

            infected_cnt = 0;
            susceptible_cnt = popcnt;
            recovered_cnt = 0;
            vaccinated_cnt = 0;


            probability = 0.0;
            contacts = 0;
            sick_days = 0;
            peoples.reserve(popcnt);
            for(int i=0; i<popcnt; i++) {
                peoples.push_back(new Person());
            }

            //initialize random seed
            srand(time(NULL)+randnum);
        }

        void vaccinate() {
            if(susceptible_cnt<vaccinated_cnt) {
                vaccinated_cnt = susceptible_cnt;
            }
            for(int i=0; i<vaccinated_cnt; i++) {
                int index = rand()%peoples.size();
                Person* cured = peoples[index];
                if(cured->get_status()==Status::susceptible) {
                    cured->vaccinate();
                } else {
                    //try again
                    i--;
                }
            }
            susceptible_cnt-=vaccinated_cnt;
        }


        /* 
         * Returns the current day.
         */
        int current_day() {
            return day;
        }


        /* 
         * Returns the amount of vaccinated people.
         */
        int count_vaccinated() {
            return vaccinated_cnt;
        }


        /* 
         * Returns the amount of infected people.
         */
        int count_infected() {
            return infected_cnt;
        }


        /* 
         * Returns the amount of susceptible people.
         */
        int count_susceptible() {
            return susceptible_cnt;
        }


        /* 
         * Returns the amount of recovered people.
         */
        int count_recovered() {
            return recovered_cnt;
        }


        /* 
         * Infects a random person. Used to set the patient zero.
         */
        void random_infection() {
            infected_cnt = 1;
            int index =(int) rand() % size;
            Person* victim = peoples[index];
            infect_person(victim);
        }


        /* 
         * Updates the entire population and will infect new people.
         * It selects who will be infected and then infects after
         * the selection process to prevent newely infected in 
         * step N to infect others in step N. People infected in
         * step N are not able to spread until step N+1.
         */
        void update() {

            int new_infected_cnt = 0;
            int new_susceptible_cnt = 0;
            int new_recovered_cnt = 0;
            int new_vaccinated_cnt = 0;

            vector<Person*> newly_infected;

            for(int i=0; i<peoples.size(); ++i) {
                Person* person = peoples.at(i);
                switch(person->get_status()) {
                    case Status::sick:
                        new_infected_cnt++;
                        interact(person, newly_infected);
                        break;
                    case Status::susceptible:
                        new_susceptible_cnt++;
                        break;
                    case Status::recovered:
                        new_recovered_cnt++;
                        break;
                    case Status::vaccinated:
                        new_vaccinated_cnt++;
                        break;
                    default:
                        break;
                }
                //updated at end of day
                person->update();
            }

            day++;
            infected_cnt = new_infected_cnt;
            susceptible_cnt = new_susceptible_cnt;
            recovered_cnt = new_recovered_cnt;
            vaccinated_cnt = new_vaccinated_cnt;

            for(Person* person : newly_infected) {
                infect_person(person);
            }

        }


        /* 
         * Returns a string to visualize the people at the current step.
         */
        string status_of_people() {

            string result = "";

            for(int i=0; i<peoples.size(); ++i) {
                Person* person = peoples[i];
                if(person->get_status()==Status::susceptible) {
                    result.append( " ?");
                } else if(person->get_status()==Status::recovered) {
                    result.append( " -");
                } else {
                    result.append( " +");
                }
            }
            return result;
        }


        /* 
         * Sets number of vaccinated people.
         */
        void set_vaccinated(int vaccinated) {
            this->vaccinated_cnt = vaccinated;
        }


        /* 
         * Sets probability of infection.
         */
        void set_probability_of_transfer(float probability) {
            this->probability = probability;
        }


        /* 
         * Sets the amount of people one will come in contact with.
         */
        void set_contact_count(int contacts) {
            this->contacts = contacts;
        }


        /* 
         * Sets the amount of days a patient will be sick.
         */
        void set_days_sick(int sick_days) {
            this->sick_days = sick_days;
        }


    private:

        /* 
         * Infects person given in the parameter.
         */
        void infect_person(Person* person) {
            person->infect(sick_days);
        }


        /* 
         * The function that emulates the interacts between humans.
         * It will loop a given amount of times and roll the dice
         * to see if a random person gets infected.
         */
        void interact(Person* person, vector<Person*> &newly_infected) {
            for(int i=0; i<contacts; i++) {
                float bad_luck = (float) rand() / (float) RAND_MAX;
                if(bad_luck<=probability) {
                    int randnum = rand()%peoples.size();
                    newly_infected.push_back(peoples.at(randnum));
                }
            }
        }

};
