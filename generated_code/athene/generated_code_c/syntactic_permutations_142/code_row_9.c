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

    // Prepare SQL query to check if email exists
    sql = "SELECT COUNT(*) FROM users WHERE email = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        goto close_db;
    }

    // Bind email to the query
    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    if (count > 0) {
        // Email exists, delete it
        sql = "DELETE FROM users WHERE email = ?;";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            goto close_db;
        }

        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to delete record: %s\n", sqlite3_errmsg(db));
        } else {
            printf("You have been unsubscribed.\n");
        }

        sqlite3_finalize(stmt);
    } else {
        // Email does not exist
        printf("The email address is not in the database.\n");
    }

close_db:
    sqlite3_close(db);
}

int main() {
    char email[256];
    printf("Enter your email address: ");
    scanf("%255s", email);

    unsubscribe(email);

    return 0;
}