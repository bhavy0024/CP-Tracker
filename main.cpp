#include <bits/stdc++.h>
#include "problem.h"
using namespace std;

int main()
{
    Problem p;

    p.id = 1;
    p.platform = "Codeforces";
    p.problem_name = "Two Sum";
    p.difficulty = "Easy";
    p.rating = 800;
    p.topic = "Implementation";
    p.solved = true;
    p.time_taken = 20;
    p.notes = "Good for beginners";
    p.revision_date = "2026-06-30";

    cout << "ID : " << p.id << endl;
    cout << "Platform : " << p.platform << endl;
    cout << "Problem : " << p.problem_name << endl;
    cout << "Difficulty : " << p.difficulty << endl;
    cout << "Rating : " << p.rating << endl;
    cout << "Topic : " << p.topic << endl;
    cout << "Solved : " << (p.solved ? "Yes" : "No") << endl;
    cout << "Time Taken : " << p.time_taken << " min" << endl;
    cout << "Notes : " << p.notes << endl;
    cout << "Revision Date : " << p.revision_date << endl;

    return 0;
}