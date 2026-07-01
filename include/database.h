#ifndef DATABASE_H
#define DATABASE_H

#include <bits/stdc++.h>
#include "../sqlite/sqlite3.h"
#include "problem.h"
using namespace std;

class Database
{
private:
    sqlite3 *db;

public:
    Database();
    ~Database();

    void execute(const string &query);

    void createTable();
    void insertProblem(Problem p);
    void displayProblems();

    void updateNotes(int id, string notes);
    void deleteProblem(int id);

    void searchByName(string name);
    void filterByPlatform(string platform);
    void filterByDifficulty(string difficulty);
    void filterByRating(int minR, int maxR);

    void showStats();
    void showRevisionList();
    void exportToCSV();
};

#endif