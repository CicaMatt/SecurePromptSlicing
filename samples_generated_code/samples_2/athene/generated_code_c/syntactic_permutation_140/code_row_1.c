#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    int rc;
    const char *sql;
    char *zErrMsg = 0;
    const char *data = "Callback function called";
    const char *username = "testuser";

    rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sql = "SELECT COUNT(*) FROM users WHERE username = ?";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return !exists;
}