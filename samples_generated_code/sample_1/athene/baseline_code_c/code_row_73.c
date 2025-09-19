#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(const char *username) {
    sqlite3 *db;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND role='moderator';";
    int rc;
    int count = 0;

    char *dbname = getenv("DB_NAME");
    if (dbname == NULL) return -1; // Error handling for missing env var

    rc = sqlite3_open(dbname, &db);
    if (rc != SQLITE_OK) return -1; // Error handling for database connection

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return -1; // Error handling for SQL preparation
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return count > 0;
}