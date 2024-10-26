#include <iostream>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    const char *dbPath = "D:/CPP/library-system/db/example.db";
    int exit = sqlite3_open(dbPath, &db);
    if (exit)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Opened database successfully!" << std::endl;
    }
    sqlite3_close(db);
    return 0;
}
