#include "../include/logger.h"

#include <fstream>
#include <ctime>

using namespace std;

void writeLog(string msg)
{
    ofstream file("log.txt", ios::app);

    time_t now = time(0);

    file << ctime(&now) << " : " << msg << endl;
}