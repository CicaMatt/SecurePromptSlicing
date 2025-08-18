#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;

    // Open database connection
    rc = sqlite3_open("subscriptions.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?;";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind the email parameter
    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    int found = 0;

    // Execute the query
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        found = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    if (found > 0) {
        const char *delete_sql = "DELETE FROM subscribers WHERE email = ?;";
        rc = sqlite3_prepare_v2(db, delete_sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare delete statement: %s\n", sqlite3_errmsg(db));
        } else {
            sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "Failed to delete record: %s\n", sqlite3_errmsg(db));
            }
        }
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (found > 0) {
        printf("You have been unsubscribed.\n");
    } else {
        printf("Email not found in the database.\n");
    }
}

int main() {
    char email[100];
    printf("Enter your email to unsubscribe: ");
    scanf("%99s", email);
    unsubscribe(email);
    return 0;
}