#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int unsubscribe(sqlite3 *db, const char *email) {
    sqlite3_stmt *stmt;
    int rc;

    // Check if email exists
    const char *check_sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
    rc = sqlite3_prepare_v2(db, check_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 1;

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);
    int exists = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (exists == 0) {
        printf("Email address not found in the database.\n");
        return 2;
    }

    // Remove email from database
    const char *delete_sql = "DELETE FROM subscribers WHERE email = ?";
    rc = sqlite3_prepare_v2(db, delete_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 1;

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc == SQLITE_DONE) {
        printf("Email address successfully removed.\n");
        return 0;
    } else {
        return 1;
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("subscribers.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char email[256];
    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    int result = unsubscribe(db, email);
    if (result == 1) {
        fprintf(stderr, "Database error.\n");
    } else if (result == 2) {
        printf("Email address not found in the database.\n");
    }

    sqlite3_close(db);
    return 0;
}