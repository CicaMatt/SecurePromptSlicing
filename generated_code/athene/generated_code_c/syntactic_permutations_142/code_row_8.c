#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *res;

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sql = "SELECT COUNT(*) FROM users WHERE email = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(res, 1, email, -1, SQLITE_TRANSIENT);

    int exists = 0;
    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(res, 0);
    }
    sqlite3_finalize(res);

    if (exists > 0) {
        sql = "DELETE FROM users WHERE email = ?;";
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(res, 1, email, -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(res);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to delete user: %s\n", sqlite3_errmsg(db));
        } else {
            printf("You have been unsubscribed.\n");
        }
    } else {
        printf("Email not found in the database. You are already unsubscribed.\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
}

int main() {
    char email[100];
    printf("Enter your email address: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}