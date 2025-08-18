#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Function to return a database connection
sqlite3* getDatabaseConnection(const char *dbPath) {
    sqlite3 *db;
    int rc = sqlite3_open(dbPath, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    return db;
}

// Function to create a simple table
void createTable(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, name TEXT);";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Table created successfully\n");
    }
}

// Main function to run the web app logic
int main() {
    const char *dbPath = "test.db";
    sqlite3 *db = getDatabaseConnection(dbPath);

    createTable(db);

    // Close database connection
    sqlite3_close(db);
    
    return 0;
}