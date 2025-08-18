#include <stdio.h>
#include <sqlite3.h>

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    char *err_msg = NULL;

    const char *sql = "SELECT CASE WHEN EXISTS (SELECT 1 FROM users WHERE username = ?) THEN 1 ELSE 0 END;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    return exists;
}

int main() {
    sqlite3 *db;
    const char *db_file = "example.db";
    int rc;

    if ((rc = sqlite3_open(db_file, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *username = "testuser";
    int exists = check_username_exists(db, username);

    printf("Username '%s' exists: %s\n", username, exists ? "true" : "false");

    sqlite3_close(db);
    return 0;
}