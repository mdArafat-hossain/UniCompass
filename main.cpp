#include <iostream>
#include <string>
#include "Utilities/Utilities.h"
#include "Algorithms/Algorithms.h"
using namespace std;

class UniCompass
{
public:
    int budget;
    string district;
    string university_type;

    void introduction()
    {
        cout << string(15,' ') << "Welcome to UniCompass" << endl << endl;
    }

    void input()
    {
        cout << "Please tell us your preference" << endl;

        cout << "Budget : ";
        budget = int_validation(); //check if the input is only int or not

        cout << "District : ";
        cin.ignore(); //ignore /n from previous cin
        getline(cin, district);
        district = lowercase_convert(district); //convert all uppercase to lowercase

        cout << "University type (press 0 to see all types of universities): ";
        getline(cin,university_type);
        university_type = lowercase_convert(university_type);
    }

    void filter_algorithm()
    {

        int count = filter(budget, district, university_type);

        cout << "Matching universities: " << count << endl;

        if (count > 0)
        {
            mergeSort();
        }
    }
};

int main()
{
    UniCompass obj;
    obj.introduction();
    obj.input();
    obj.filter_algorithm();

    return 0;
}
