#include <stdio.h>
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

    // Prepare SQL query to check email existence
    sql = "SELECT COUNT(*) FROM subscriptions WHERE email = ?";

    int exists = 0;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        goto exit;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (exists > 0) {
        // Email found, prepare SQL to delete
        sql = "DELETE FROM subscriptions WHERE email = ?";
        
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            goto exit;
        }

        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to delete record: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("Email address '%s' has been unsubscribed.\n", email);
        }
    } else {
        printf("Email address '%s' not found in the database.\n", email);
    }

exit:
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char email[100];
    printf("Enter your email to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}