#include <bits/stdc++.h>
#include "../include/database.h"
using namespace std;

int main()
{
    Database d;
    d.createTable();
    Problem p;
    int ch;

    while (true)
    {
        cout << "\n==============================\n";
        cout << "       CP TRACKER v1.0        \n";
        cout << "==============================\n";
        cout << "1. Add Problem\n";
        cout << "2. View Problems\n";
        cout << "3. Search Problem\n";
        cout << "4. Filter by Platform\n";
        // cout << "5. Filter by Difficulty\n";
        cout << "5. Filter by Rating\n";
        cout << "6. Revision List 🔁\n";
        cout << "7. Show Statistics\n";
        cout << "8. Export to CSV\n";
        cout << "9. Exit\n";
        cout << "==============================\n";
        cout << "Enter Choice: ";

        cin >> ch;
        if (ch == 1)
        {
            cout << "Enter ID : ";
            cin >> p.id;

            cin.ignore();

            cout << "Enter Platform : ";
            getline(cin, p.platform);

            cout << "Enter Problem Name : ";
            getline(cin, p.problem_name);

            cout << "Enter Difficulty : ";
            getline(cin, p.difficulty);

            cout << "Enter Rating : ";
            cin >> p.rating;

            cin.ignore();

            cout << "Enter Notes : ";
            getline(cin, p.notes);

            cout << "Revision Date (YYYY-MM-DD): ";
            getline(cin, p.revision_date);
            cout << "\nAdding new problem...\n";
            d.insertProblem(p);
        }
        if (ch == 2)
        {
            d.displayProblems();
        }
        if (ch == 3)
        {
            string name;
            cin.ignore();

            cout << "Enter problem name to search: ";
            getline(cin, name);

            d.searchByName(name);
        }
        if (ch == 4)
        {
            string platform;
            cin.ignore();

            cout << "Enter platform: ";
            getline(cin, platform);

            d.filterByPlatform(platform);
        }
        if (ch == 5)
        {
            int l, r;

            cout << "Enter min rating: ";
            cin >> l;

            cout << "Enter max rating: ";
            cin >> r;

            d.filterByRating(l, r);
        }
        if (ch == 6)
        {
            d.showRevisionList();
            // break;
        }
        if (ch == 7)
        {
            d.showStats();
        }
        if (ch == 8)
        {
            d.exportToCSV();
        }

        if (ch == 9)
        {
            cout << "\nExiting CP Tracker... Happy Coding! 🚀\n";
            break;
        }
    }

    return 0;
}