#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int unsubscribe(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "DELETE FROM subscribers WHERE email = ?";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        printf("Email address '%s' has been unsubscribed.\n", email);
    } else {
        printf("Email address '%s' was not found in the database.\n", email);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int main() {
    char email[100];
    printf("Enter your email address to unsubscribe: ");
    scanf("%99s", email); // Limit input to prevent overflow

    return unsubscribe(email);
}