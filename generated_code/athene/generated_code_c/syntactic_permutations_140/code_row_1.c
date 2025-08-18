#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int check_username_exists(const char *username) {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = (sqlite3_column_int(stmt, 0) > 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exists;
}

int main() {
    const char *username = "testuser";
    int result = check_username_exists(username);
    if (result == -1) {
        fprintf(stderr, "An error occurred.\n");
        return 1;
    }
    printf("Username %s: %s\n", username, result ? "exists" : "does not exist");
    return 0;
}