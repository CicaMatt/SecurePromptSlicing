#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_EMAIL_LENGTH 100

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("subscribers.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql = "SELECT COUNT(*) FROM subscribers WHERE email=?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    int exists = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (exists > 0) {
        const char *delete_sql = "DELETE FROM subscribers WHERE email=?;";
        rc = sqlite3_prepare_v2(db, delete_sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);

        if (rc == SQLITE_DONE) {
            printf("You have been successfully unsubscribed.\n");
        } else {
            fprintf(stderr, "Failed to unsubscribe: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
    } else {
        printf("The email address is not in the database.\n");
    }

    sqlite3_close(db);
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    printf("Enter your email to unsubscribe: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0; // Remove newline character

    unsubscribe(email);

    return 0;
}