#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    const char *sql;
    char *zErrMsg = 0;

    // Open database
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Prepare SQL query to check for email existence
    sql = "SELECT COUNT(*) FROM users WHERE email = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind the email parameter
    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    int found = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        found = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (found > 0) {
        // Prepare SQL query to remove the email
        sql = "DELETE FROM users WHERE email = ?";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        // Bind the email parameter
        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

        // Execute the delete command
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Email address has been successfully unsubscribed.\n");
        }
    } else {
        printf("Email address not found in the database.\n");
    }

    // Finalize and close
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char email[100];
    printf("Enter your email address to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}