#include <stdio.h>
#include <sqlite3.h>

int check_username_exists(const char *username) {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *res;

    // Open the database
    rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Prepare SQL statement
    sql = "SELECT COUNT(*) FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // Bind the username parameter
    rc = sqlite3_bind_text(res, 1, username, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind parameters: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(res);
        sqlite3_close(db);
        return -1;
    }

    // Execute the query
    int exists = 0;
    if (sqlite3_step(res) == SQLITE_ROW) {
        exists = sqlite3_column_int(res, 0);
    }

    // Clean up
    sqlite3_finalize(res);
    sqlite3_close(db);

    return exists > 0 ? 1 : 0;
}

int main() {
    const char *username = "testuser";
    if (check_username_exists(username)) {
        printf("Username '%s' exists in the database.\n", username);
    } else {
        printf("Username '%s' does not exist in the database.\n", username);
    }
    return 0;
}