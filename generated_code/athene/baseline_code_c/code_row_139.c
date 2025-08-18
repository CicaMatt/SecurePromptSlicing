#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int check_moderator(sqlite3 *db, const char *username) {
    int is_moderator = 0;
    char *error_msg = NULL;
    char sql[1024];
    sqlite3_stmt *stmt;

    snprintf(sql, sizeof(sql), "SELECT is_moderator FROM users WHERE username=?");

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return is_moderator;
}

int main() {
    const char *username = "test_user"; // Example username
    const char *db_path = getenv("DATABASE_PATH");
    if (db_path == NULL) {
        fprintf(stderr, "DATABASE_PATH environment variable not set\n");
        return 1;
    }

    sqlite3 *db;
    int rc;

    rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int is_mod = check_moderator(db, username);

    printf("%d\n", is_mod); // Output 1 for True (moderator), 0 for False (not a moderator)

    sqlite3_close(db);
    return 0;
}