#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Menu {
public:
    // Methods

    // Checks if char input is valid
    // Taken from https://www.codegrepper.com/code-examples/cpp/check+if+char+in+string+c%2B%2B
    bool validUserInput(char input, string validInput);

    // Checks if int input is valid
    bool validUserInput(int input, int minValidInput, int maxValidInput);

    // Converts char col input into int input
    int charToIntInput(char input);

    // Clears console
    // Taken from https://stackoverflow.com/questions/6486289/how-can-i-clear-console
    void clearConsole();
};

#endif
