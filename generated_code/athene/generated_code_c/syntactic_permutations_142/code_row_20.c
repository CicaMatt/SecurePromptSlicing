#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    char sql[1024];
    const char *db_name = "subscribers.db";
    const char *check_sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?;";
    const char *delete_sql = "DELETE FROM subscribers WHERE email = ?;";

    // Initialize database
    rc = sqlite3_open(db_name, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Check if the email exists in the database
    int count = 0;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, check_sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    if (count > 0) {
        // Email exists, remove it from the database
        rc = sqlite3_prepare_v2(db, delete_sql, -1, &stmt, NULL);
        if (rc == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
            sqlite3_step(stmt);
            printf("Email address %s has been successfully unsubscribed.\n", email);
            sqlite3_finalize(stmt);
        }
    } else {
        // Email does not exist
        printf("The email address %s is not in the database.\n", email);
    }

    // Close database connection
    sqlite3_close(db);
}

int main() {
    char email[256];
    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);
    unsubscribe(email);
    return 0;
}