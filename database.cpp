#include "database.h"
int callback(void *data, int argc, char **argv, char **colName)
{
    for (int i = 0; i < argc; i++)
    {
        cout << colName[i] << " : " << (argv[i] ? argv[i] : "NULL") << "  ";
    }
    cout << endl;
    return 0;
}
Database::Database()
{
    sqlite3_open("cp_tracker.db", &db);
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
        "notes TEXT"
        ");";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err) == SQLITE_OK)
        cout << "Table created successfully!\n";
    else
        cout << err << endl;
}
void Database::insertProblem(Problem p)
{
    string sql =
        "INSERT INTO Problems(id, platform, problem_name, difficulty, rating, notes) VALUES(" +
        to_string(p.id) + ", '" +
        p.platform + "', '" +
        p.problem_name + "', '" +
        p.difficulty + "', " +
        to_string(p.rating) + ", '" +
        p.notes + "');";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err) == SQLITE_OK)
        cout << "Problem inserted successfully!\n";
    else
        cout << err << endl;
}
void Database::displayProblems()
{
    string sql = "SELECT * FROM Problems;";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &err) != SQLITE_OK)
        cout << err << endl;
}
void Database::updateNotes(int id, string notes)
{
    string sql =
        "UPDATE Problems SET notes = '" +
        notes +
        "' WHERE id = " +
        to_string(id) +
        ";";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err) == SQLITE_OK)
        cout << "Notes updated successfully!\n";
    else
        cout << err << endl;
}
void Database::deleteProblem(int id)
{
    string sql =
        "DELETE FROM Problems WHERE id = " +
        to_string(id) +
        ";";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err) == SQLITE_OK)
        cout << "Problem deleted successfully!\n";
    else
        cout << err << endl;
}
void Database::searchByName(string name)
{
    string sql =
        "SELECT * FROM Problems WHERE problem_name LIKE '%" + name + "%';";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &err) != SQLITE_OK)
        cout << err << endl;
}
void Database::filterByPlatform(string platform)
{
    string sql =
        "SELECT * FROM Problems WHERE platform = '" + platform + "';";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &err) != SQLITE_OK)
        cout << err << endl;
}
void Database::filterByDifficulty(string difficulty)
{
    string sql =
        "SELECT * FROM Problems WHERE difficulty = '" + difficulty + "';";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &err) != SQLITE_OK)
        cout << err << endl;
}
void Database::filterByRating(int minR, int maxR)
{
    string sql =
        "SELECT * FROM Problems WHERE rating BETWEEN " +
        to_string(minR) + " AND " + to_string(maxR) + ";";

    char *err = nullptr;

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &err) != SQLITE_OK)
        cout << err << endl;
}
void Database::showStats()
{
    char *err = nullptr;

    cout << "\n===== STATISTICS =====\n";

    string q1 = "SELECT COUNT(*) FROM Problems;";
    string q2 = "SELECT AVG(rating) FROM Problems;";
    string q3 =
        "SELECT difficulty, COUNT(*) FROM Problems GROUP BY difficulty;";
    cout << "Total Problems: ";

    sqlite3_exec(db, q1.c_str(), [](void *, int argc, char **argv, char **) -> int
                 {
        cout << argv[0] << endl;
        return 0; }, nullptr, &err);

    cout << "Average Rating: ";

    sqlite3_exec(db, q2.c_str(), [](void *, int argc, char **argv, char **) -> int
                 {
        if(argv[0]) cout << argv[0] << endl;
        else cout << "0\n";
        return 0; }, nullptr, &err);

    cout << "\nBy Difficulty:\n";

    sqlite3_exec(db, q3.c_str(), callback, nullptr, &err);
}