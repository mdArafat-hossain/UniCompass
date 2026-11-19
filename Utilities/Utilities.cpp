#include "Utilities.h"
#include <iostream>
using namespace std;

int int_validation(int condition)
{
    long long int number;

    if (condition == 1)
    {
        cin >> number;

        while (cin.fail() || number <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input! Enter a valid budget : ";
            cin >> number;
        }
    }
    else if (condition == 2)
    {

        cin >> number;

        while (cin.fail() || number <= 0 || number > 2)
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Invalid input! Enter a valid choice : ";
            cin >> number;
        }
    }

    return number;
}

string lowercase_convert(string name)
{
    for (int i = 0; i < name.length() ; i++)
    {
        if (name[i] >= 65 && name[i] <= 90)
        {
            name[i] = name[i] + 32;
        }
    }

    return name;
}
void information()
{
    //hello
}
