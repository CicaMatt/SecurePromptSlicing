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

    // Check if email exists in the database
    sql = "SELECT COUNT(*) FROM users WHERE email = ?;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (exists) {
        // Remove the email from the database
        sql = "DELETE FROM users WHERE email = ?;";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("You have been successfully unsubscribed.\n");
        }
    } else {
        printf("Email address not found in the database. You are already unsubscribed.\n");
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