#include <bits/stdc++.h>
using namespace std;


/* 
 * An enum of different status possibilities.
 */
enum class Status { susceptible, sick, recovered, vaccinated };

class Person {

    int sick_days;
    Status status;

    public:

        /* 
         * Creates a new person object.
         */
        Person() {
            status = Status::susceptible;
            sick_days = 0;
        }


        /* 
         * Updates the persons sick days.
         */
        void update() {
            if(status==Status::sick) {
                sick_days--;
                if(sick_days==0) {
                    status = Status::recovered;
                }
            }
        }


        /* 
         * Infects person if they are susceptible for given amount of days.
         */
        void infect(int days) {
            if(status==Status::susceptible) {
                sick_days = days;
                status = Status::sick;
            }
        }

        void vaccinate() {
            status = Status::vaccinated;
        }

        /* 
         * Returns true if the person is stable.
         */
        bool is_stable() {
            return status==Status::recovered;
        }


        /* 
         * Returns true if the person is infected.
         */
        bool is_infected() {
            return status==Status::sick;
        }


        /* 
         * Returns the persons status.
         */
        Status get_status() {
            return status;
        }


        /* 
         * Returns a string of their status and days to go if they are sick
         */
        string status_string() {
            std::stringstream s;
            switch(status) {
                case Status::sick:
                    s << sick_days;
                    return "sick (" + s.str() + " to go)";
                    break;
                case Status::susceptible:
                    return "susceptible";
                    break;
                case Status::recovered:
                    return "recovered";
                    break;
                case Status::vaccinated:
                    return "vaccinated";
                    break;
                default:
                    return "should not see this";
                    break;
            }
        }

};
