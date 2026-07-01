#include "../include/database.h"
#include "../include/logger.h"
#include <iomanip>
#include <fstream>
int callback(void *data, int argc, char **argv, char **colName)
{
    for (int i = 0; i < argc; i++)
    {
        cout << left << setw(18)
             << (argv[i] ? argv[i] : "NULL");
    }

    cout << endl;
    return 0;
}
Database::Database()
{
    if (sqlite3_open("cp_tracker.db", &db))
    {
        cout << "Failed to open database!\n";
        db = nullptr;
    }
}
Database::~Database()
{
    if (db)
    {
        sqlite3_close(db);
    }
}
void Database::execute(const string &query)
{
    char *err = nullptr;

    if (!db)
    {
        cout << "Database not initialized!\n";
        return;
    }

    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err) != SQLITE_OK)
    {
        cout << "DB Error: " << err << endl;
        sqlite3_free(err);
    }
}
void Database::createTable()
{
    string sql =
        "CREATE TABLE IF NOT EXISTS Problems ("
        "id INTEGER PRIMARY KEY, "
        "platform TEXT, "
        "problem_name TEXT, "
        "difficulty TEXT, "
        "rating INTEGER, "
        "notes TEXT, "
        "revision_date TEXT"
        ");";
    execute(sql);
    cout << "Table created successfully!\n";
}
void Database::insertProblem(Problem p)
{
    string sql =
        "INSERT INTO Problems(id, platform, problem_name, difficulty, rating, notes, revision_date) "
        "VALUES(?,?,?,?,?,?,?);";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cout << "Prepare failed!\n";
        return;
    }

    sqlite3_bind_int(stmt, 1, p.id);
    sqlite3_bind_text(stmt, 2, p.platform.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, p.problem_name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, p.difficulty.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, p.rating);
    sqlite3_bind_text(stmt, 6, p.notes.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, p.revision_date.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cout << "Insert failed!\n";
    }
    else
    {
        cout << "Problem inserted successfully!\n";
        writeLog("Problem Added");
    }

    sqlite3_finalize(stmt);
}
void Database::displayProblems()
{
    // string sql = "SELECT * FROM Problems;";
    string sql = "SELECT id, platform, problem_name, difficulty, rating, notes, revision_date FROM Problems;";

    cout << "\n";
    cout << left
         << setw(6) << "ID"
         << setw(15) << "Platform"
         << setw(25) << "Problem"
         << setw(12) << "Difficulty"
         << setw(10) << "Rating"
         << setw(25) << "Notes"
         << setw(15) << "Revision"
         << endl;

    cout << string(108, '-') << endl;

    sqlite3_exec(db, sql.c_str(), callback, nullptr, nullptr);
}
void Database::updateNotes(int id, string notes)
{
    string sql = "UPDATE Problems SET notes = ? WHERE id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        cout << "Prepare failed!\n";
        return;
    }

    sqlite3_bind_text(stmt, 1, notes.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        cout << "Notes updated successfully!\n";
        // cout << "Notes updated successfully!\n";
        writeLog("Notes Updated");
    }
    else
        cout << "Update failed!\n";

    sqlite3_finalize(stmt);
}
void Database::deleteProblem(int id)
{
    string sql =
        "DELETE FROM Problems WHERE id = " + to_string(id) + ";";
    execute(sql);
    cout << "Problem deleted successfully!\n";
    // cout << "Notes updated successfully!\n";
    writeLog("Notes Updated");
}
void Database::searchByName(string name)
{
    string sql =
        "SELECT * FROM Problems WHERE problem_name LIKE '%" + name + "%';";
    sqlite3_exec(db, sql.c_str(), callback, nullptr, nullptr);
}
void Database::filterByPlatform(string platform)
{
    string sql =
        "SELECT * FROM Problems WHERE platform = '" + platform + "';";
    sqlite3_exec(db, sql.c_str(), callback, nullptr, nullptr);
}
void Database::filterByDifficulty(string difficulty)
{
    string sql =
        "SELECT * FROM Problems WHERE difficulty = '" + difficulty + "';";
    sqlite3_exec(db, sql.c_str(), callback, nullptr, nullptr);
}
void Database::filterByRating(int minR, int maxR)
{
    string sql =
        "SELECT * FROM Problems WHERE rating BETWEEN " +
        to_string(minR) + " AND " + to_string(maxR) + ";";
    sqlite3_exec(db, sql.c_str(), callback, nullptr, nullptr);
}
void Database::showStats()
{
    cout << "\n===== STATISTICS =====\n";
    char *err = nullptr;
    string q1 = "SELECT COUNT(*) FROM Problems;";
    string q2 = "SELECT AVG(rating) FROM Problems;";
    string q3 = "SELECT difficulty, COUNT(*) FROM Problems GROUP BY difficulty;";
    cout << "Total Problems: ";
    sqlite3_exec(db, q1.c_str(), [](void *, int argc, char **argv, char **) -> int
                 {
            cout << (argv[0] ? argv[0] : "0") << endl;
            return 0; }, nullptr, nullptr);
    cout << "Average Rating: ";
    string q4 = "SELECT MAX(revision_date) FROM Problems;";
    sqlite3_exec(db, q2.c_str(), [](void *, int argc, char **argv, char **) -> int
                 {
            cout << (argv[0] ? argv[0] : "0") << endl;
            return 0; }, nullptr, nullptr);
    cout << "Last Revision Date: ";

    sqlite3_exec(
        db,
        q4.c_str(),
        [](void *, int argc, char **argv, char **) -> int
        {
            if (argv[0])
                cout << argv[0] << endl;
            else
                cout << "N/A" << endl;
            return 0;
        },
        nullptr,
        &err);
    cout << "\nBy Difficulty:\n";
    sqlite3_exec(db, q3.c_str(), callback, nullptr, nullptr);
}
void Database::showRevisionList()
{
    cout << "\n===== PROBLEMS TO REVISE =====\n";

    string sql =
        "SELECT id, problem_name, revision_date "
        "FROM Problems "
        "ORDER BY revision_date ASC;";

    sqlite3_exec(db, sql.c_str(), callback, nullptr, nullptr);
}
void Database::exportToCSV()
{
    ofstream file("problems.csv");

    if (!file.is_open())
    {
        cout << "Cannot create CSV file!\n";
        return;
    }

    file << "ID,Platform,Problem,Difficulty,Rating,Notes,Revision Date\n";

    string sql =
        "SELECT id, platform, problem_name, difficulty, rating, notes, revision_date FROM Problems;";

    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        file
            << sqlite3_column_int(stmt, 0) << ","
            << sqlite3_column_text(stmt, 1) << ","
            << sqlite3_column_text(stmt, 2) << ","
            << sqlite3_column_text(stmt, 3) << ","
            << sqlite3_column_int(stmt, 4) << ","
            << sqlite3_column_text(stmt, 5) << ","
            << sqlite3_column_text(stmt, 6)
            << endl;
    }

    sqlite3_finalize(stmt);
    file.close();

    cout << "\nProblems exported to problems.csv successfully!\n";
    writeLog("CSV Exported");
}