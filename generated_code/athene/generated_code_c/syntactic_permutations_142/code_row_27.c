#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "subscribers.db"
#define TABLE_NAME "subscribers"

int unsubscribe(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "DELETE FROM subscribers WHERE email = ?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to unsubscribe: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Successfully unsubscribed: %s\n", email);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return rc == SQLITE_DONE ? 0 : 1;
}

int main() {
    char email[256];
    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    if (unsubscribe(email) == 0) {
        printf("Unsubscription process completed successfully.\n");
    } else {
        printf("Failed to complete unsubscription.\n");
    }

    return 0;
}