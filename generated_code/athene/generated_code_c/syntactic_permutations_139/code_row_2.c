#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(const char *username) {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *stmt;

    const char *db_path = getenv("DB_PATH");
    if (db_path == NULL) return 0;

    rc = sqlite3_open(db_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sql = "SELECT COUNT(*) FROM users WHERE username=? AND is_moderator=1";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result > 0;
}