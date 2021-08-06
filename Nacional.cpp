#include <ctime>
#include <string>
#include <vector>
#include "Date.h"
#include "Estadual.h"
#include "Nacional.h"

using namespace std;

Nacional::Nacional(string name, vector<Estadual> states)
{
    _name = name;
    _states = states;
}

string Nacional::name()
{
    return _name;
}

vector<Estadual> Nacional::states()
{
    return _states;
}


int Nacional::deathsOnDate(time_t date)
{
    int deaths = 0;

    for (auto it = _states.begin(); it != _states.end(); it++) {
        deaths += it->deathsOnDate(date);
    }

    return deaths;
}

int Nacional::totalDeathsOnDate(time_t date)
{
    int deaths = 0;

    for (auto it = _states.begin(); it != _states.end(); it++) {
        deaths += it->totalDeathsOnDate(date);
    }

    return deaths;
}

float Nacional::movingAvarage(time_t date, int numberOfDays)
{
    if (numberOfDays <= 1) {
        throw "Days of moving avarage should be greater than 1.";
    }

    time_t auxDate = date;
    int totalDeaths = 0;

    for (int i = 0; i < numberOfDays; i++) {
        int deaths = deathsOnDate(auxDate);
        totalDeaths += deaths;

        auxDate = Date::previousDay(auxDate);
    }

    return totalDeaths / numberOfDays;
}

float Nacional::growRate(time_t date, int numberOfDays)
{
    time_t previousDay = Date::previousDay(date);

    float movingAvarageOnDate = movingAvarage(date, numberOfDays);
    float movingAvarageOnPreviousDay = movingAvarage(previousDay, numberOfDays);

    return (movingAvarageOnDate / movingAvarageOnPreviousDay) - 1;
}

Estadual Nacional::lowestGrow(time_t date, int numberOfDays)
{
    Estadual stateWithLowestGrow = _states[0];

    for (auto it = _states.begin(); it != _states.end(); it++) {
        if (it->growRate(date, numberOfDays) < stateWithLowestGrow.growRate(date, numberOfDays)) {
            stateWithLowestGrow = *it;
        }
    }

    return stateWithLowestGrow;
}

Estadual Nacional::highestGrow(time_t date, int numberOfDays)
{
    Estadual stateWithHighestGrow = _states[0];

    for (auto it = _states.begin(); it != _states.end(); it++) {
        if (it->growRate(date, numberOfDays) > stateWithHighestGrow.growRate(date, numberOfDays)) {
            stateWithHighestGrow = *it;
        }
    }

    return stateWithHighestGrow;
}
