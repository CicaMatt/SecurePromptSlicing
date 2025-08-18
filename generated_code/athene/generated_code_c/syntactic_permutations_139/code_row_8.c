#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int is_moderator(const char *username) {
    sqlite3 *db;
    int rc = sqlite3_open(getenv("DATABASE_URL"), &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND is_moderator=1";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    int is_mod = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_mod = (int)sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return is_mod > 0;
}

int main() {
    const char *username = "example_user";
    if (is_moderator(username)) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
    return 0;
}