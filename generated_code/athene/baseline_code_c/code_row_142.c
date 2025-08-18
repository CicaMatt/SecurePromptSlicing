#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int unsubscribe(sqlite3 *db, const char *email) {
    sqlite3_stmt *stmt;
    int rc;

    // Prepare SQL statement to check if email exists
    const char *sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 1;

    // Bind the email parameter
    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    // Execute the query and get the result
    int found = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        found = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (found > 0) {
        // Prepare SQL statement to delete email
        const char *delete_sql = "DELETE FROM subscribers WHERE email = ?;";
        rc = sqlite3_prepare_v2(db, delete_sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) return 1;

        // Bind the email parameter
        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        // Execute the delete statement
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (rc == SQLITE_DONE) {
            printf("You have been unsubscribed successfully.\n");
        } else {
            printf("Failed to unsubscribe. Please try again later.\n");
        }
    } else {
        printf("The email address is not in the database.\n");
    }

    return 0;
}

int main() {
    sqlite3 *db;
    const char *email = "test@example.com"; // Example email, should be replaced with actual input
    int rc;

    // Open the database
    rc = sqlite3_open("subscribers.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    unsubscribe(db, email);

    // Close the database
    sqlite3_close(db);

    return 0;
}