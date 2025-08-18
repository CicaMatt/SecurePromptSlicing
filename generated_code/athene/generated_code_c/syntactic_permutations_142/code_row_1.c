#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    const char *sql;
    char *zErrMsg = 0;

    // Open database
    rc = sqlite3_open("subscriptions.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Prepare SQL query to check if email exists
    sql = "SELECT COUNT(*) FROM subscribers WHERE email=?;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    // Bind email to the query
    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    int exists = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (exists > 0) {
        // Prepare SQL query to delete the email
        sql = "DELETE FROM subscribers WHERE email=?;";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            sqlite3_close(db);
            return;
        }

        // Bind email to the query
        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        // Execute the delete query
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Failed to remove email: %s\n", zErrMsg);
        } else {
            printf("Email address removed successfully.\n");
        }
    } else {
        printf("This email is not in our database.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char email[256];
    printf("Enter your email address to unsubscribe: ");
    scanf("%s", email);
    unsubscribe(email);
    return 0;
}