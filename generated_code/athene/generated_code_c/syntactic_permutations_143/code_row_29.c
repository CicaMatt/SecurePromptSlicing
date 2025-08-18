#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    char email[100];
} User;

int handle_unsubscribe(sqlite3 *db, const char *email) {
    int rc;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT email FROM users WHERE email=?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 1;

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    int found = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        found = 1;
    }
    sqlite3_finalize(stmt);

    if (found) {
        const char *delete_sql = "DELETE FROM users WHERE email=?";
        rc = sqlite3_prepare_v2(db, delete_sql, -1, &stmt, NULL);
        if (rc != SQLITE_OK) return 1;

        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc == SQLITE_DONE) {
            printf("User %s is not subscribed.\n", email);
            return 0;
        } else {
            return 1;
        }
    } else {
        printf("Email %s not found in the database.\n", email);
        return 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    handle_unsubscribe(db, email);

    sqlite3_close(db);
    return 0;
}