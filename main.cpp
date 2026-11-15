#include <iostream>
#include <string>
#include "Utilities/Utilities.h"
using namespace std;

class UniCompass
{
public:
    string budget;
    string in_district; string district;
    string in_university_type, university_type;

    void introduction()
    {
        cout << string(15,' ') << "Welcome to UniCompass" << endl << endl;
    }

    void input()
    {
        cout << "Please tell us your preference" << endl;

        cout << "Budget : ";
        budget = int_input(); //check if the input is only int or not and convert it into string

        cout << "District : ";
        cin.ignore(); //ignore /n from previous cin
        getline(cin, in_district);
        district = lowercase_convert(in_district); //convert all uppercase to lowercase

        cout << "University type (press 0 to see all types of universities): ";
        getline(cin, in_university_type);
        university_type = lowercase_convert(in_university_type);
    }
};

int main()
{
    UniCompass obj;
    obj.introduction();
    obj.input();

    return 0;
}
