#include "Utilities.h"
#include <iostream>
using namespace std;

string int_input()
{
    long long int number;

    cin >> number;

    while (cin.fail() || number <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid input! Enter a valid budget (Without coma) : ";
        cin >> number;
    }

    return to_string(number);
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
