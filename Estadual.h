#ifndef ESTADUAL_H
#define ESTADUAL_H
#include <ctime>
#include <string>
#include <map>

using namespace std;

class Estadual
{
    private:
        string _uf;
        map<time_t, int> _deathsPerDay;
    public:
        Estadual(string uf, map<time_t, int> deathsPerDay);
        string uf();
        map<time_t, int> deathsPerDay();
        int deathsOnDate(time_t date);
        int totalDeathsOnDate(time_t date);
        float movingAvarage(time_t date, int numberOfDays);
        float growRate(time_t date, int nubmerOfDays);
};

#endif
