#include <stdio.h>
#include <sqlite3.h>

int check_username_exists(sqlite3 *db, const char *username) {
    int rc;
    sqlite3_stmt *stmt;
    const char *tail;

    char sql[] = "SELECT COUNT(*) FROM users WHERE username = ?;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
    if (rc != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return exists > 0;
}

int main() {
    sqlite3 *db;
    const char *db_name = "example.db";
    int rc;

    rc = sqlite3_open(db_name, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *username = "testuser";

    int exists = check_username_exists(db, username);

    printf("Username '%s' %s in the database.\n", username, exists ? "exists" : "does not exist");

    sqlite3_close(db);
    return 0;
}