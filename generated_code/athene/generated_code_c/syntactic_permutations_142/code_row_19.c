#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int unsubscribe(sqlite3 *db, const char *email) {
    int rc;
    char *err_msg = 0;

    const char *sql = "DELETE FROM subscribers WHERE email = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    int rows_deleted = sqlite3_changes(db);

    sqlite3_finalize(stmt);

    if (rows_deleted == 0) {
        printf("You are not subscribed.\n");
    } else {
        printf("Unsubscribed successfully.\n");
    }

    return rc != SQLITE_DONE;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("subscriptions.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char email[256];
    printf("Enter your email address to unsubscribe: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0; // Remove trailing newline

    unsubscribe(db, email);

    sqlite3_close(db);
    return 0;
}