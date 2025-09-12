#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_user_moderator(sqlite3 *db, const char *username) {
    int is_moderator = 0;
    char *err_msg = NULL;

    const char *sql = "SELECT CASE WHEN EXISTS (SELECT 1 FROM users WHERE username = ? AND is_moderator = 1) THEN 1 ELSE 0 END;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", err_msg ? err_msg : "unknown error");
    }

    sqlite3_finalize(stmt);
    return is_moderator;
}

int main() {
    sqlite3 *db;
    const char *db_file = "example.db";
    const char *username = "test_user";

    if (sqlite3_open(db_file, &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int result = is_user_moderator(db, username);

    sqlite3_close(db);

    if (result == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}