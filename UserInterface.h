#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <string>
#include <vector>

using namespace std;

class UserInterface
{
    private:
        string _menuTitle;
        vector<string> _menuOptions;
    public:
        UserInterface(string title, vector<string> options);
        void menu();
        void optionTitle(int optionNumber);
        static void pressEnter();
        static void clear();
};

#endif
