#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    char *err_msg = 0;

    rc = sqlite3_open("subscriptions.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql = "SELECT COUNT(*) FROM subscribers WHERE email=?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    int found = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        found = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (found > 0) {
        const char *delete_sql = "DELETE FROM subscribers WHERE email=?;";
        rc = sqlite3_prepare_v2(db, delete_sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to delete subscriber: %s\n", err_msg);
        } else {
            printf("You have been successfully unsubscribed.\n");
        }
    } else {
        printf("Email not found in the database. You are already unsubscribed.\n");
    }

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