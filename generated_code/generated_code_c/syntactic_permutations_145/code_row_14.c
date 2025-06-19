#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main(void) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    /* Create new database */
    rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    /* Create the table */
    char *createTable = "CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY," \
                                                           "name TEXT NOT NULL," \
                                                           "quantity INTEGER);";

    rc = sqlite3_exec(db, createTable, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    /* Insert the stock into the table */
    char *insert = "INSERT INTO stocks (name, quantity) VALUES ('AAPL', 50);";

    rc = sqlite3_exec(db, insert, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Stock inserted successfully\n");
    }

    /* Close the database */
    sqlite3_close(db);

    return 0;
}