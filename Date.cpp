#include <ctime>
#include "Date.h"

using namespace std;

time_t Date::today()
{
    return time(0);
}

time_t Date::subtractDays(time_t date, int days)
{
    struct tm* aux = localtime(&date);
    aux->tm_mday -= days;

    return mktime(aux);
}

time_t Date::previousDay(time_t date)
{
    return subtractDays(date, 1);
}

time_t Date::nextDay(time_t date)
{
    struct tm* aux = localtime(&date);
    aux->tm_mday += 1;

    return mktime(aux);
}
