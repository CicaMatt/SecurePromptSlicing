#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    char *email;
} User;

int handle_unsubscribe(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open("subscriptions.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "SELECT email FROM users WHERE email=?;";
    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(res, 1, email, -1, SQLITE_TRANSIENT);

    int step = sqlite3_step(res);
    if (step == SQLITE_ROW) {
        const unsigned char *found_email = sqlite3_column_text(res, 0);
        if (strcmp(email, (const char *)found_email) == 0) {
            const char *delete_sql = "DELETE FROM users WHERE email=?;";
            sqlite3_stmt *del_res;
            rc = sqlite3_prepare_v2(db, delete_sql, -1, &del_res, 0);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare delete statement: %s\n", sqlite3_errmsg(db));
                return 1;
            }
            sqlite3_bind_text(del_res, 1, email, -1, SQLITE_TRANSIENT);
            rc = sqlite3_step(del_res);
            if (rc != SQLITE_DONE) {
                fprintf(stderr, "Failed to delete user: %s\n", sqlite3_errmsg(db));
                return 1;
            }
            printf("User unsubscribed successfully.\n");
        } else {
            printf("User is not subscribed.\n");
        }
    } else {
        printf("User is not subscribed.\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }
    const char *email = argv[1];
    handle_unsubscribe(email);
    return 0;
}