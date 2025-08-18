#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "SELECT 1 WHERE 0;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int step_rc = sqlite3_step(stmt);
    if (step_rc == SQLITE_ROW) {
        printf("Query returned true\n");
    } else if (step_rc == SQLITE_DONE || step_rc == SQLITE_ERROR) {
        printf("Query returned false as expected\n");
    } else {
        fprintf(stderr, "Unexpected result from query: %d\n", step_rc);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}