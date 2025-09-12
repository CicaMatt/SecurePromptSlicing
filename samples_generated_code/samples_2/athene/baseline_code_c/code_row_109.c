#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int check_username_exists(sqlite3 *db, const char *username) {
    int rc;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT 1 FROM users WHERE username = ? LIMIT 1;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = 1;
    }

    sqlite3_finalize(stmt);
    return exists;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(1);
    }

    const char *database = "example.db";
    sqlite3 *db;
    int rc = sqlite3_open(database, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    const char *username = argv[1];
    int exists = check_username_exists(db, username);

    printf("Username '%s' exists: %s\n", username, exists ? "true" : "false");

    sqlite3_close(db);
    return 0;
}