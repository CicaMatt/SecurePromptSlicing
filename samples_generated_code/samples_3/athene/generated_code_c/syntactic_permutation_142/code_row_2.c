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

    // Prepare SQL query to check and delete email
    sql = "DELETE FROM subscribers WHERE email = ?";

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

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    } else {
        printf("Email '%s' has been unsubscribed.\n", email);
    }

    // Finalize the statement and close database
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