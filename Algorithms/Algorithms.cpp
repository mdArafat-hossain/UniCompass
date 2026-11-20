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

void mergeSort(int Sort)
{
    struct University
    {
        string name, district, type, course, scholarship;
        string email, number, website, academicCalendar;
        int fee, ranking;
    };

    vector<University> universities;

    // Read filtered data
    ifstream file("Filtered.csv");

    if (!file)
    {
        cout << "Error! Try Again";
        return;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        University u;

        string fee, ranking;

        getline(ss, u.name, ',');
        getline(ss, u.district, ',');
        getline(ss, u.type, ',');
        getline(ss, u.course, ',');
        getline(ss, fee, ',');
        getline(ss, u.scholarship, ',');
        getline(ss, ranking, ',');
        getline(ss, u.academicCalendar, ',');
        getline(ss, u.email, ',');
        getline(ss, u.number, ',');
        getline(ss, u.website);

        try
        {
            u.fee = stoi(fee);
            u.ranking = stoi(ranking);
        }
        catch (...)
        {
            continue;
        }

        universities.push_back(u);
    }

    file.close();

    int n = universities.size();

    if (n == 0)
    {
        cout << "No universities found!";
        remove("Filtered.csv");
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
                bool takeLeft;

                if (Sort == 1)
                {
                    // Sort by overall ranking
                    if (universities[i].ranking != universities[j].ranking)
                        takeLeft = universities[i].ranking < universities[j].ranking;
                    else
                        takeLeft = universities[i].fee <= universities[j].fee;
                }
                else
                {
                    // Sort by lowest tuition fee
                    if (universities[i].fee != universities[j].fee)
                        takeLeft = universities[i].fee < universities[j].fee;
                    else
                        takeLeft = universities[i].ranking <= universities[j].ranking;
                }

                if (takeLeft)
                    temp[k++] = universities[i++];
                else
                    temp[k++] = universities[j++];
            }

            while (i < mid)
                temp[k++] = universities[i++];

            while (j < right)
                temp[k++] = universities[j++];
        }

        universities.swap(temp);
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
        cout << "Average Tuition Fee: " << u.fee << endl;
        cout << "Scholarship: " << u.scholarship << endl;
        cout << "Ranking: " << u.ranking << endl;
        cout << "Academic Calendar System: " << u.academicCalendar << endl;
        cout << "Email: " << u.email << endl;
        cout << "Phone Number: " << u.number << endl;
        cout << "Official Website: " << u.website << endl;

        cout << "-----------------------------\n";
    }

    // UNIVERSITY SUMMARY
    int lowestFee = universities[0].fee;
    int highestFee = universities[0].fee;

    int bestRanking = universities[0].ranking;

    int publicCount = 0;
    int privateCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (universities[i].fee < lowestFee)
            lowestFee = universities[i].fee;

        if (universities[i].fee > highestFee)
            highestFee = universities[i].fee;

        if (universities[i].ranking < bestRanking)
            bestRanking = universities[i].ranking;

        if (universities[i].type == "public")
            publicCount++;

        else if (universities[i].type == "private")
            privateCount++;
    }

    cout << "\n========== UNIVERSITY SUMMARY ==========\n";

    cout << "Total Matching Universities: " << n << endl;
    cout << "Lowest Tuition Fee: " << lowestFee << endl;
    cout << "Highest Tuition Fee: " << highestFee << endl;
    cout << "Best Overall Ranking: " << bestRanking << endl;
    cout << "Public Universities: " << publicCount << endl;
    cout << "Private Universities: " << privateCount << endl;

    cout << "========================================\n";

    // Delete temporary file
    remove("Filtered.csv");
}

