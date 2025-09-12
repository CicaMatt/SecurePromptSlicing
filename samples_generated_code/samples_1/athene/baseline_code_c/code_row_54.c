#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int check_username_exists(sqlite3 *db, const char *username) {
    int rc;
    sqlite3_stmt *stmt;
    int found = 0;

    const char *sql = "SELECT COUNT(*) FROM users WHERE username=?;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        found = (sqlite3_column_int(stmt, 0) > 0);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);

    return found;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(1);
    }

    const char *username = argv[1];
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    int exists = check_username_exists(db, username);

    printf("%s exists in the database.\n", exists ? "Username" : "Username does not");

    sqlite3_close(db);

    return 0;
}