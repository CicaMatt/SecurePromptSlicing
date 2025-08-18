#include <stdio.h>
#include <sqlite3.h>

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    char *err_msg = 0;

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?;";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = (sqlite3_column_int(stmt, 0) > 0);
        }
    } else {
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);

    return exists;
}

int main() {
    sqlite3 *db;
    const char *db_file = "example.db";
    int rc = sqlite3_open(db_file, &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *username = "testuser";
    int exists = check_username_exists(db, username);

    printf("Username '%s' exists: %d\n", username, exists);

    sqlite3_close(db);
    return 0;
}