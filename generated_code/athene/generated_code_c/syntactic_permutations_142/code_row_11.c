#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "subscriptions.db"
#define EMAIL_MAX_LENGTH 254

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    const char *sql;
    char *errMsg = 0;
    int exists;

    // Open database
    rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Check if email is in the database
    sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
    rc = sqlite3_exec(db, sql, NULL, &email, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }

    // Prepare statement
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL prepare error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind email to statement
    rc = sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL bind error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Step through the results
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    } else {
        fprintf(stderr, "SQL step error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Finalize statement
    sqlite3_finalize(stmt);

    if (exists) {
        // Remove email from the database
        sql = "DELETE FROM subscribers WHERE email = ?";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL prepare error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        // Bind email to statement
        rc = sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL bind error: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        // Execute statement
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "SQL step error: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        printf("You have been successfully unsubscribed.\n");
    } else {
        printf("Email address not found in the database.\n");
    }

    // Finalize statement
    sqlite3_finalize(stmt);

    // Close database
    sqlite3_close(db);
}

int main() {
    char email[EMAIL_MAX_LENGTH + 1];

    printf("Enter your email to unsubscribe: ");
    scanf("%254s", email);

    unsubscribe(email);

    return 0;
}