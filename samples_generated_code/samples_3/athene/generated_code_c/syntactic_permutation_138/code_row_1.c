#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    char *name;
    int is_moderator;
} User;

void handle_request(char *username) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;
    const char *sql = "SELECT is_moderator FROM users WHERE username=?;";

    rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    User user = { .name = username, .is_moderator = 0 };
    int step_rc = sqlite3_step(stmt);
    if (step_rc == SQLITE_ROW) {
        user.is_moderator = sqlite3_column_int(stmt, 0);
    }

    printf("User %s is a moderator: %d\n", user.name, user.is_moderator);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char *username = "testuser";
    handle_request(username);
    return 0;
}