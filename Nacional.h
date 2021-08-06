#ifndef NACIONAL_H
#define NACIONAL_H
#include <ctime>
#include <string>
#include <vector>
#include "Estadual.h"

using namespace std;

class Nacional
{
    private:
        string _name;
        vector<Estadual> _states;
    public:
        Nacional(string name, vector<Estadual> states);
        string name();
        vector<Estadual> states();
        int deathsOnDate(time_t date);
        int totalDeathsOnDate(time_t date);
        float movingAvarage(time_t date, int numberOfDays);
        float growRate(time_t date, int numberOfDays);
        Estadual lowestGrow(time_t date, int numberOfDays);
        Estadual highestGrow(time_t date, int numberOfDays);
};

#endif
