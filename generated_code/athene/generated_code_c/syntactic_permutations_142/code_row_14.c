#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int unsubscribe(sqlite3 *db, const char *email) {
    int rc;
    char *sql = "DELETE FROM subscribers WHERE email=?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) return rc;

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    int rowsDeleted = sqlite3_changes(db);

    sqlite3_finalize(stmt);

    if (rowsDeleted > 0) {
        printf("You have been unsubscribed successfully.\n");
    } else {
        printf("Email address not found in the database.\n");
    }

    return rc;
}

int main() {
    sqlite3 *db;
    int rc;
    char email[100];

    printf("Enter your email to unsubscribe: ");
    scanf("%99s", email);

    rc = sqlite3_open("subscribers.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = unsubscribe(db, email);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);

    return 0;
}