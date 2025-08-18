#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *stmt;

    // Open database
    rc = sqlite3_open("subscriptions.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Prepare SQL query to check if email exists
    sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind email to the query
    rc = sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Bind error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Execute the query
    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (exists > 0) {
        // Email exists in database, prepare SQL to delete it
        sql = "DELETE FROM subscribers WHERE email = ?;";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        // Bind email to the delete query
        rc = sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Bind error: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        // Execute the delete
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Delete failed: %s\n", sqlite3_errmsg(db));
        } else {
            printf("You have been successfully unsubscribed.\n");
        }
    } else {
        printf("The email address is not in our database.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    const char *email = "example@example.com";
    unsubscribe(email);
    return 0;
}