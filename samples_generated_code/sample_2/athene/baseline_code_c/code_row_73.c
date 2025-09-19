#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(const char *username) {
    sqlite3 *db;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND role='moderator';";
    int rc;
    int count = 0;

    const char *db_filename = getenv("DB_FILENAME");
    if (db_filename == NULL) {
        fprintf(stderr, "Error: DB_FILENAME environment variable not set.\n");
        exit(1);
    }

    rc = sqlite3_open(db_filename, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare SQL statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(res, 0);
    } else {
        fprintf(stderr, "No data fetched.\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return count > 0;
}

int main() {
    const char *username = getenv("USER_USERNAME");
    if (username == NULL) {
        fprintf(stderr, "Error: USER_USERNAME environment variable not set.\n");
        exit(1);
    }

    int is_mod = is_moderator(username);
    printf("%d\n", is_mod);

    return 0;
}