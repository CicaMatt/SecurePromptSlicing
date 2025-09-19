#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int unsubscribe(sqlite3 *db, const char *email) {
    sqlite3_stmt *stmt;
    int result = 0;

    // Prepare SQL to check if email exists
    const char *sql = "SELECT COUNT(*) FROM users WHERE email = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Bind the email parameter
    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    // Execute the query and get the result
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        if (count > 0) {
            // Email exists, prepare SQL to delete it
            const char *delete_sql = "DELETE FROM users WHERE email = ?";
            if (sqlite3_prepare_v2(db, delete_sql, -1, &stmt, NULL) != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
                return 1;
            }

            // Bind the email parameter
            sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

            // Execute the delete query
            if (sqlite3_step(stmt) != SQLITE_DONE) {
                fprintf(stderr, "Failed to delete user: %s\n", sqlite3_errmsg(db));
                return 1;
            }
        } else {
            // Email does not exist
            printf("This email address is not in our database.\n");
            result = -1;
        }
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    return result;
}

int main() {
    sqlite3 *db;
    const char *email;

    // Open the database (assuming it's called 'users.db')
    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Enter your email address to unsubscribe: ");
    scanf("%ms", &email);

    int result = unsubscribe(db, email);

    if (result == 0) {
        printf("You have been successfully unsubscribed.\n");
    } else if (result == -1) {
        printf("This email address is not in our database.\n");
    }

    // Free the allocated memory for the email
    free((void *)email);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}