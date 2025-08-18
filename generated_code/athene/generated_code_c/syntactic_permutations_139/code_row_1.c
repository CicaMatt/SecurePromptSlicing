#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(const char *username) {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *res;
    char *dbname = getenv("DATABASE_URL");
    if (dbname == NULL) return 0;

    rc = sqlite3_open(dbname, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sql = "SELECT COUNT(*) FROM users WHERE username=? AND is_moderator=1";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(res, 1, username, -1, SQLITE_TRANSIENT);

    int count = 0;
    if (sqlite3_step(res) == SQLITE_ROW) {
        count = sqlite3_column_int(res, 0);
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return count > 0;
}

int main() {
    const char *username = "test_user";
    int is_mod = is_moderator(username);
    printf("%d\n", is_mod);
    return 0;
}