#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(const char *username) {
    sqlite3 *db;
    const char *dbname = getenv("DATABASE_URL");
    int rc = sqlite3_open(dbname, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND is_moderator=1";
    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(res, 1, username, -1, SQLITE_TRANSIENT);

    int result = 0;
    if (sqlite3_step(res) == SQLITE_ROW) {
        result = sqlite3_column_int(res, 0) > 0;
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
    return result;
}