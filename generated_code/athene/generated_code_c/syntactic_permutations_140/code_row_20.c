#include <stdio.h>
#include <sqlite3.h>

int check_username_exists(sqlite3 *db, const char *username) {
    int user_exists = 0;
    char *err_msg = NULL;

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            user_exists = sqlite3_column_int(stmt, 0) > 0;
        }
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_finalize(stmt);
    return user_exists;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *username = "testuser";
    int exists = check_username_exists(db, username);

    printf("User '%s' exists: %s\n", username, exists ? "true" : "false");

    sqlite3_close(db);
    return 0;
}