#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(const char *username) {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *res;
    char *dbname = getenv("DB_NAME");
    char *dbuser = getenv("DB_USER");
    char *dbpass = getenv("DB_PASS");

    if (sqlite3_open_v2(dbname, &db, SQLITE_OPEN_READONLY, NULL)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sql = "SELECT is_moderator FROM users WHERE username=? AND is_moderator=1";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare query: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(res, 1, username, -1, SQLITE_TRANSIENT);

    int step_rc = sqlite3_step(res);
    int is_mod = (step_rc == SQLITE_ROW) ? 1 : 0;

    sqlite3_finalize(res);
    sqlite3_close(db);

    return is_mod;
}