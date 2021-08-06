#ifndef DATE_H
#define DATE_H
#include <ctime>

using namespace std;

class Date
{
    public:
        static time_t today();
        static time_t subtractDays(time_t date, int days);
        static time_t previousDay(time_t date);
        static time_t nextDay(time_t date);
};
#endif
