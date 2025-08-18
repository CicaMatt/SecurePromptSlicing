#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    int rc;

    // Open the database
    rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='your_table';";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Execute the query
    int step = sqlite3_step(stmt);

    if (step == SQLITE_ROW) {
        printf("Table 'your_table' exists.\n");
    } else {
        printf("Table 'your_table' does not exist.\n");
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}