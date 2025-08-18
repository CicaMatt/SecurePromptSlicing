#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(char *email) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open the database
    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "DELETE FROM users WHERE email = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_close(db);
        return;
    }

    // Bind the email parameter
    rc = sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind parameters: %s\n", err_msg);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE) {
        printf("Email address '%s' has been unsubscribed.\n", email);
    } else if (rc == SQLITE_ROW) {
        fprintf(stderr, "Unexpected row returned from DELETE operation.\n");
    } else {
        int count;
        char *count_sql = "SELECT COUNT(*) FROM users WHERE email = ?;";
        sqlite3_stmt *count_stmt;
        rc = sqlite3_prepare_v2(db, count_sql, -1, &count_stmt, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_text(count_stmt, 1, email, -1, SQLITE_STATIC);
            rc = sqlite3_step(count_stmt);
            if (rc == SQLITE_ROW) {
                count = sqlite3_column_int(count_stmt, 0);
            }
            sqlite3_finalize(count_stmt);
        }

        if (count == 0) {
            printf("Email address '%s' is not in the database.\n", email);
        } else {
            fprintf(stderr, "Failed to unsubscribe: %s\n", err_msg);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char email[100];
    printf("Enter your email address to unsubscribe: ");
    scanf("%99s", email); // Read up to 99 characters to avoid buffer overflow

    unsubscribe(email);

    return 0;
}