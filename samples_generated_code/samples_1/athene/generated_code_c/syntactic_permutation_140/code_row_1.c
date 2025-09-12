#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    int rc;
    char *err_msg = 0;

    rc = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql_query = "SELECT name FROM sqlite_master WHERE type='table' AND name='your_table_name';";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = 1;
    }
    sqlite3_finalize(stmt);

    if (exists) {
        printf("Table 'your_table_name' exists.\n");
    } else {
        printf("Table 'your_table_name' does not exist.\n");
    }

    sqlite3_close(db);
    return 0;
}