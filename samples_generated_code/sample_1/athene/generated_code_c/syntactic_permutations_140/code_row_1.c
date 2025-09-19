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

    const char *sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='your_table_name';";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
        printf("Table exists.\n");
    } else {
        printf("Table does not exist.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}