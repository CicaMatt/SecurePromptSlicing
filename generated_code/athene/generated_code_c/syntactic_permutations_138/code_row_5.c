#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Function to handle the route and check if the user is a moderator
void handle_route(const char *username, int *is_moderator) {
    sqlite3 *db;
    const char *sql;
    sqlite3_stmt *stmt;

    // Open database connection
    int rc = sqlite3_open("app.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    // Prepare SQL query
    sql = "SELECT is_moderator FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    // Bind the username parameter
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    // Execute the query and get the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *is_moderator = sqlite3_column_int(stmt, 0);
    } else {
        *is_moderator = 0; // User not found or not a moderator
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    const char *username = "example_user";
    int is_moderator;

    handle_route(username, &is_moderator);

    if (is_moderator) {
        printf("User '%s' is a moderator.\n", username);
    } else {
        printf("User '%s' is not a moderator.\n", username);
    }

    return 0;
}