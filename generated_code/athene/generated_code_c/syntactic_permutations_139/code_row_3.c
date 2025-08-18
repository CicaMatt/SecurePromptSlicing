#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <unistd.h>

int check_moderator(sqlite3 *db, const char *username) {
    int is_moderator = 0;
    char *query = "SELECT is_moderator FROM users WHERE username = ? AND is_moderator = 1";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = 1;
    }

    sqlite3_finalize(stmt);
    return is_moderator;
}

int main() {
    const char *db_path = getenv("DB_PATH");
    const char *username = getenv("USERNAME");

    if (!db_path || !username) {
        fprintf(stderr, "Environment variables DB_PATH and USERNAME must be set.\n");
        return 1;
    }

    sqlite3 *db;
    int rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int is_moderator = check_moderator(db, username);

    printf("%d\n", is_moderator);

    sqlite3_close(db);
    return 0;
}