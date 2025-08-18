#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char *argv[]) {
    sqlite3 *db;
    int rc;
    const char *sql;
    char *zErrMsg = 0;
    const char *username = "testuser";
    int exists = 0;

    rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    sql = "SELECT COUNT(*) FROM users WHERE username = ?";

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return(1);
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL prepare error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    if (exists > 0) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exists > 0 ? 0 : 1;
}