#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Date.h"
#include "Estadual.h"
#include "Nacional.h"
#include "UserInterface.h"

using namespace std;

int MOVING_AVARAGE_DAYS = 5;

Nacional randomBrazilianData(time_t endDate)
{
    time_t startDate = Date::subtractDays(endDate, MOVING_AVARAGE_DAYS);

    vector<Estadual> states;

    vector<string> statesNames = {
        "AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", "MT", "MS",
        "MG", "PA", "PB", "PR", "PE", "PI", "RJ", "RN", "RS", "RO","RR", "SC",
        "SP", "SE", "TO"
    };
    for (auto it = statesNames.begin(); it != statesNames.end(); it++) {
        map<time_t, int> deathsPerDay;

        time_t auxDate = startDate;
        while (auxDate <= endDate) {
            int deaths = rand() % 100;
            deathsPerDay[auxDate] = deaths;

            auxDate = Date::nextDay(auxDate);
        }

        Estadual state(*it, deathsPerDay);

        states.push_back(state);
    }

    return Nacional("Brazil", states);
}

int main(int argc, char *argv[])
{
    try {
        time_t referenceDate = Date::today();
        Nacional brazil = randomBrazilianData(referenceDate);

        UserInterface ui(
            "COVID-19 Deaths",
            {
                "Moving avarage",
                "Grow rate (states)",
                "Grow rate (country)",
                "Grow rate (max & min)",
                "Total deaths",
                "Raw data"
            }
        );

        string option;
        do {
            ui.menu();
            cin >> option;

            if (option == "1") {
                ui.optionTitle(stoi(option));

                float countryMovingAvarage = brazil.movingAvarage(referenceDate, MOVING_AVARAGE_DAYS);
                cout << brazil.name() << ": " << countryMovingAvarage << endl << endl;

                vector<Estadual> states = brazil.states();
                for (auto it = states.begin(); it != states.end(); it++) {
                    float stateMovingAvarage = it->movingAvarage(referenceDate, MOVING_AVARAGE_DAYS);
                    cout << it->uf() << ": " << stateMovingAvarage << endl;
                }

                UserInterface::pressEnter();
            } else if (option == "2") {
                ui.optionTitle(stoi(option));

                vector<Estadual> states = brazil.states();

                cout << "------------" << endl;

                cout << "High" << endl << endl;
                for (auto it = states.begin(); it != states.end(); it++) {
                    float growRate = it->growRate(referenceDate, MOVING_AVARAGE_DAYS) * 100;
                    if (growRate > 10) {
                        cout << it->uf() << ": " << growRate << "%" << endl;
                    }
                }
                cout << "------------" << endl;

                cout << "Low" << endl << endl;
                for (auto it = states.begin(); it != states.end(); it++) {
                    float growRate = it->growRate(referenceDate, MOVING_AVARAGE_DAYS) * 100;
                    if (growRate < -10) {
                        cout << it->uf() << ": " << growRate << "%" << endl;
                    }
                }
                cout << "------------" << endl;

                cout << "Stable" << endl << endl;
                for (auto it = states.begin(); it != states.end(); it++) {
                    float growRate = it->growRate(referenceDate, MOVING_AVARAGE_DAYS) * 100;
                    if (growRate <= 10 && growRate >= -10) {
                        cout << it->uf() << ": " << growRate << "%" << endl;
                    }
                }
                cout << "------------" << endl;

                UserInterface::pressEnter();
            } else if (option == "3") {
                ui.optionTitle(stoi(option));

                float growRate = brazil.growRate(referenceDate, MOVING_AVARAGE_DAYS) * 100;
                string status;
                if (growRate > 10) {
                    status = "High";
                } else if (growRate < -10) {
                    status = "Low";
                } else {
                    status = "Stable";
                }

                cout << brazil.name() << ": " << growRate << "% (" << status << ")" << endl;

                UserInterface::pressEnter();
            } else if (option == "4") {
                ui.optionTitle(stoi(option));

                Estadual stateWithLowestGrow = brazil.lowestGrow(referenceDate, MOVING_AVARAGE_DAYS);
                float lowestGrow = stateWithLowestGrow.growRate(referenceDate, MOVING_AVARAGE_DAYS) * 100;

                Estadual stateWithHighestGrow = brazil.highestGrow(referenceDate, MOVING_AVARAGE_DAYS);
                float highestGrow = stateWithHighestGrow.growRate(referenceDate, MOVING_AVARAGE_DAYS) * 100;

                cout << "Lowest Grow:  " << stateWithLowestGrow.uf() << " (" << lowestGrow << "%)";
                cout << endl;
                cout << "Highest Grow: " << stateWithHighestGrow.uf() << " (" << highestGrow << "%)";
                cout << endl;

                UserInterface::pressEnter();
            } else if (option == "5") {
                ui.optionTitle(stoi(option));

                cout << brazil.name() << ": " << brazil.totalDeathsOnDate(referenceDate) << endl;
                cout << endl;

                vector<Estadual> states = brazil.states();
                for (auto it = states.begin(); it != states.end(); it++) {
                    cout << it->uf() << ": " << it->totalDeathsOnDate(referenceDate) << endl;
                }

                UserInterface::pressEnter();
            } else if (option == "6") {
                ui.optionTitle(stoi(option));

                bool firstItem = true;
                vector<Estadual> states = brazil.states();
                for (auto it1 = states.begin(); it1 != states.end(); it1++) {
                    if (firstItem) {
                        cout << brazil.name();

                        map<time_t, int> deathsPerDay = it1->deathsPerDay();
                        for (auto it2 = deathsPerDay.begin(); it2 != deathsPerDay.end(); it2++) {
                            int deaths = brazil.deathsOnDate(it2->first);

                            cout << "\t" << deaths;
                        }
                        cout << endl << endl;

                        firstItem = false;
                    }

                    cout << it1->uf();

                    map<time_t, int> deathsPerDay = it1->deathsPerDay();
                    for (auto it2 = deathsPerDay.begin(); it2 != deathsPerDay.end(); it2++) {
                        int deaths = it2->second;

                        cout << "\t" << deaths;
                    }

                    cout << endl;
                }

                UserInterface::pressEnter();
            } else if (option == "0") {
                UserInterface::clear();
            } else {
                UserInterface::clear();
                cout << "Invalid option." << endl;

                UserInterface::pressEnter();
            }
        } while (option != "0");

        return 0;
    } catch(const char* message) {
        cerr << endl << "Error: " << message << endl;
        return 1;
    }
}
