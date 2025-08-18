#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(char *email) {
    sqlite3 *db;
    int rc;
    char *err_msg = 0;

    // Open database
    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "DELETE FROM users WHERE email = ?";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_DONE) {
        printf("Email address %s successfully unsubscribed.\n", email);
    } else if (rc == SQLITE_ROW) {
        // This case should not happen for a DELETE statement
        fprintf(stderr, "Unexpected row returned from database.\n");
    } else {
        printf("Email address %s is not in the database.\n", email);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char email[256];
    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    unsubscribe(email);

    return 0;
}