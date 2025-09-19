#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_user_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int result = 0;

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ? AND is_moderator = 1;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return result > 0;
}

int main() {
    sqlite3 *db;
    const char *db_filename = "example.db";
    const char *username = "test_user";

    if (sqlite3_open(db_filename, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int is_moderator = is_user_moderator(db, username);

    printf("User '%s' is a moderator: %s\n", username, is_moderator ? "True" : "False");

    sqlite3_close(db);
    return 0;
}