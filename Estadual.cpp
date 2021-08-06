#include <ctime>
#include <map>
#include <string>
#include "Estadual.h"
#include "Date.h"

using namespace std;

Estadual::Estadual(string uf, map<time_t, int> deathsPerDay)
{
    _uf = uf;
    _deathsPerDay = deathsPerDay;
};

string Estadual::uf()
{
    return _uf;
}

map<time_t, int> Estadual::deathsPerDay()
{
    return _deathsPerDay;
}

int Estadual::deathsOnDate(time_t date)
{
    if (_deathsPerDay.find(date) == _deathsPerDay.end()) {
        return 0;
    } else {
        return _deathsPerDay.find(date)->second;
    }
}

int Estadual::totalDeathsOnDate(time_t referenceDate)
{
    int totalDeaths = 0;

    for (auto it = _deathsPerDay.begin(); it != _deathsPerDay.end(); it++) {
        time_t date = it->first;
        int deaths = it->second;

        if (date <= referenceDate) {
            totalDeaths += deaths;
        }
    }

    return totalDeaths;
}

float Estadual::movingAvarage(time_t date, int numberOfDays)
{
    if (numberOfDays <= 1) {
        throw "Days of moving avarage should be greater than 1.";
    }

    time_t auxDate = date;
    int totalDeaths = 0;

    for (int i = 0; i < numberOfDays; i++) {
        totalDeaths += deathsOnDate(auxDate);

        auxDate = Date::previousDay(auxDate);
    }

    return totalDeaths / numberOfDays;
}

float Estadual::growRate(time_t date, int numberOfDays)
{
    time_t previousDay = Date::previousDay(date);

    float movingAvarageOnDate = movingAvarage(date, numberOfDays);
    float movingAvarageOnPreviousDay = movingAvarage(previousDay, numberOfDays);

    return (movingAvarageOnDate / movingAvarageOnPreviousDay) - 1;
}
