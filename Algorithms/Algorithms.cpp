#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include "Algorithms.h"
using namespace std;

int filter(int tuition_fee, string district, string university_type)
{
    //university name, district, university type, available course, tuition fee, scholarship, ranking;

    int count = 0;
    string name, dist, type, course, fee, scholarship, ranking, time, line;
    string email, number, website;

    ifstream file("University_Information.csv");
    ofstream temp("Filtered.csv");

    if (!file)
    {
        cout << "File not found!";
        return 0;
    }

    while (getline(file, name, ','))
    {
        getline(file, dist, ',');
        getline(file, type, ',');
        getline(file, course, ',');
        getline(file, fee, ',');
        getline(file, scholarship, ',');
        getline(file, ranking, ',');
        getline(file, time, ',');
        getline(file, email, ',');
        getline(file, number, ',');
        getline(file, website);

        if (district == dist)
        {
            if (university_type == type || university_type == "all")
            {
                int Fee = stoi(fee);

                if (Fee <= tuition_fee)
                {
                    temp << name << ","
                         << dist << ","
                         << type << ","
                         << course << ","
                         << fee << ","
                         << scholarship << ","
                         << ranking << ","
                         << time << ","
                         << email << ","
                         << number << ","
                         << website << endl;
                    count++;
                }

            }
        }

    }

    file.close();
    temp.close();
    return count;
}

void mergeSort()
{
    struct University
    {
        string name, district, type, course, scholarship;
        string email, number, website;
        int fee, ranking, semesterMonth, monthsLeft;
    };

    vector<University> universities;

    // Get current month
    time_t now = time(0);
    tm *currentTime = localtime(&now);

    int currentMonth = currentTime->tm_mon + 1;

    // Read filtered data
    ifstream file("Filtered.csv");

    if (!file)
    {
        cout << "Filtered file not found!";
        return;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        University u;

        string fee, ranking, semester;

        getline(ss, u.name, ',');
        getline(ss, u.district, ',');
        getline(ss, u.type, ',');
        getline(ss, u.course, ',');
        getline(ss, fee, ',');
        getline(ss, u.scholarship, ',');
        getline(ss, ranking, ',');
        getline(ss, semester, ',');
        getline(ss, u.email, ',');
        getline(ss, u.number, ',');
        getline(ss, u.website);

        try
        {
            u.fee = stoi(fee);
            u.ranking = stoi(ranking);
            u.semesterMonth = stoi(semester);
        }
        catch (...) //Catches any exception if something goes wrong
        {
            continue;
        }

        if (u.semesterMonth < 1 || u.semesterMonth > 12)
            continue;

        // Calculate months remaining
        u.monthsLeft =
            (u.semesterMonth - currentMonth + 12) % 12;

        universities.push_back(u);
    }

    file.close();

    int n = universities.size();

    if (n == 0)
    {
        cout << "No universities found!";
        return;
    }

    // MERGE SORT
    vector<University> temp(n);

    for (int width = 1; width < n; width *= 2)
    {
        for (int left = 0; left < n; left += 2 * width)
        {
            int mid = min(left + width, n);
            int right = min(left + 2 * width, n);

            int i = left;
            int j = mid;
            int k = left;

            while (i < mid && j < right)
            {
                if (universities[i].monthsLeft <
                        universities[j].monthsLeft)
                {
                    temp[k++] = universities[i++];
                }
                else if (universities[i].monthsLeft >
                         universities[j].monthsLeft)
                {
                    temp[k++] = universities[j++];
                }
                else if (universities[i].ranking <=
                         universities[j].ranking)
                {
                    temp[k++] = universities[i++];
                }
                else
                {
                    temp[k++] = universities[j++];
                }
            }

            while (i < mid)
                temp[k++] = universities[i++];

            while (j < right)
                temp[k++] = universities[j++];
        }

        universities = temp;
    }

    // DISPLAY RESULTS
    cout << "\n========== UNICOMPASS ==========\n";

    cout << "Total Universities: " << n << endl;

    for (int i = 0; i < n; i++)
    {
        University u = universities[i];

        cout << "\nUniversity: " << u.name << endl;
        cout << "District: " << u.district << endl;
        cout << "University Type: " << u.type << endl;
        cout << "Available Course: " << u.course << endl;
        cout << "Tuition Fee: " << u.fee << endl;
        cout << "Scholarship: " << u.scholarship << endl;
        cout << "Ranking: " << u.ranking << endl;
        cout << "Emai: " << u.email << endl;
        cout << "Phone Number: " << u.number << endl;
        cout << "Official Website: " << u.website << endl;

        if (u.monthsLeft == 0)
        {
            cout << "Semester starts this month!\n";
        }
        else
        {
            cout << "Semester starts in "
                 << u.monthsLeft << " months.\n";
        }

        cout << "-----------------------------\n";
    }

    // NEAREST SEMESTER
    cout << "\n========== SEMESTER SUMMARY ==========\n";

    cout << "Nearest upcoming semester: "
         << universities[0].name << endl;

    cout << "Time remaining: "
         << universities[0].monthsLeft
         << " months" << endl;

    remove("Filtered.csv");
}
