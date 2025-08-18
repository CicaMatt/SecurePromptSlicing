#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "subscribers.db"
#define TABLE_NAME "subscribers"

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    const char *sql;
    char *errMsg = 0;

    // Open database
    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Check if email exists in the database
    char query[100];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM %s WHERE email = ?", TABLE_NAME);
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        goto close_db;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    int count = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (count > 0) {
        // Remove the email from the database
        snprintf(query, sizeof(query), "DELETE FROM %s WHERE email = ?", TABLE_NAME);
        rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            goto close_db;
        }

        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to delete record: %s\n", sqlite3_errmsg(db));
        } else {
            printf("You have been successfully unsubscribed.\n");
        }
        sqlite3_finalize(stmt);
    } else {
        printf("The email address is not in the database.\n");
    }

close_db:
    sqlite3_close(db);
}

int main() {
    char email[100];
    printf("Enter your email address to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}