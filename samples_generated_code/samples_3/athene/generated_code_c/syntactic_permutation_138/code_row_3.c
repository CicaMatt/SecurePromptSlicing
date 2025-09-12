#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    char *username;
} User;

void handle_request(User *user) {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[100];
    snprintf(sql, sizeof(sql), "SELECT * FROM users WHERE username='%s'", user->username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    int found = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        found = 1;
    }

    if (found) {
        printf("User exists.\n");
    } else {
        printf("User does not exist.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void define_route() {
    User user = { .username = "testuser" };
    handle_request(&user);
}

int main() {
    define_route();
    return 0;
}