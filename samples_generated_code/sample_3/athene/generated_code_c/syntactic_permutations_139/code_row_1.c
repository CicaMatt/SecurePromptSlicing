#include <stdio.h>
#include <sqlite3.h>

int is_user_moderator(sqlite3 *db, const char *username) {
    int is_mod = 0;
    char *err_msg = NULL;
    sqlite3_stmt *stmt;

    const char *sql = "SELECT CASE WHEN EXISTS (SELECT 1 FROM users WHERE username = ? AND is_moderator = 1) THEN 1 ELSE 0 END";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_mod = sqlite3_column_int(stmt, 0);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", err_msg);
    }

    sqlite3_finalize(stmt);
    return is_mod;
}

int main() {
    sqlite3 *db;
    const char *db_file = "example.db";
    
    if (sqlite3_open(db_file, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *username = "test_user";
    int is_mod = is_user_moderator(db, username);

    printf("User '%s' is a moderator: %s\n", username, is_mod ? "True" : "False");

    sqlite3_close(db);
    return 0;
}