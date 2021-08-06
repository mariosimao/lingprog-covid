#include <iostream>
#include <string>
#include <vector>
#include "UserInterface.h"

using namespace std;

UserInterface::UserInterface(string menuTitle, vector<string> menuOptions)
{
    _menuTitle = menuTitle;
    _menuOptions = menuOptions;
}

void UserInterface::menu()
{
    clear();
    cout << endl;
    cout << _menuTitle << endl << endl;

    for (long unsigned int i = 0; i < _menuOptions.size(); i++)
    {
        cout << i+1 << ". " << _menuOptions[i] << endl;
    }
    cout << "0. Exit" << endl << endl;

    cout << "Option: ";
}

void UserInterface::optionTitle(int optionNumber)
{
    clear();
    cout << endl;
    cout << _menuOptions[optionNumber - 1] << endl << endl;
}

void UserInterface::pressEnter()
{
    cout << endl << "Press enter to return.";
    cin.ignore();
    cin.ignore();
}

void UserInterface::clear()
{
    system("clear");
}
