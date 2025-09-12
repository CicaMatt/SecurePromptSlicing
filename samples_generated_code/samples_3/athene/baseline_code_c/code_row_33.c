#include <stdio.h>
#include <sqlite3.h>

int user_exists(sqlite3 *db, const char *username) {
    int rc;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return exists;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *username = "testuser";
    int exists = user_exists(db, username);

    printf("User '%s' exists: %s\n", username, exists ? "true" : "false");

    sqlite3_close(db);
    return 0;
}