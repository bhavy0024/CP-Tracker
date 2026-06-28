#ifndef DATABASE_H
#define DATABASE_H

#include <bits/stdc++.h>
#include "sqlite3.h"
#include "problem.h"
using namespace std;

class Database
{
public:
    sqlite3 *db;

    Database();

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
};

#endif