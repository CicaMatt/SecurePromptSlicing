#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    char* path;
    void (*handler)(void);
} Route;

void routeHandler() {
    sqlite3 *db;
    int rc;
    const char *sql = "SELECT is_moderator FROM users WHERE username=?;";
    sqlite3_stmt *res;

    rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare query: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    // Assuming we have a username for the user
    const char *username = "some_user";
    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);

    int step_rc = sqlite3_step(res);
    if (step_rc == SQLITE_ROW) {
        int is_moderator = sqlite3_column_int(res, 0);
        printf("User is moderator: %d\n", is_moderator);
    } else {
        fprintf(stderr, "No user found or error in query.\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
}

int main() {
    Route route = {"/check-moderator", routeHandler};
    route.handler();
    return 0;
}