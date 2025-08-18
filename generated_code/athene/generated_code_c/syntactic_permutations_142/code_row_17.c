#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "subscribers.db"
#define EMAIL_MAX_LENGTH 254

int unsubscribe(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql = "DELETE FROM subscribers WHERE email = ?;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        printf("You have been successfully unsubscribed.\n");
    } else if (rc == SQLITE_ROW) {
        printf("Unexpected row found during unsubscribe operation.\n");
    } else {
        printf("Email address not found in the database. You are already unsubscribed.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int main() {
    char email[EMAIL_MAX_LENGTH + 1];
    printf("Enter your email to unsubscribe: ");
    scanf("%254s", email);

    if (unsubscribe(email) != 0) {
        fprintf(stderr, "Failed to unsubscribe.\n");
        return 1;
    }

    return 0;
}