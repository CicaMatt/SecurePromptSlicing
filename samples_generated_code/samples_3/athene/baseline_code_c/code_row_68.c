#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    const char *method;
    const char *path;
    void (*handler)(void);
} Route;

void init_web_app() {
    // Placeholder for web app initialization
}

void add_route(Route route) {
    // Placeholder for adding a route to the web app
}

void check_moderator_status() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *sql = "SELECT is_moderator FROM users WHERE username = ?;";
    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    const char *username = "testuser"; // Example username
    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);

    int step = sqlite3_step(res);
    if (step == SQLITE_ROW) {
        int is_moderator = sqlite3_column_int(res, 0);
        printf("User %s is a moderator: %d\n", username, is_moderator);
    } else {
        fprintf(stderr, "No data found for user %s\n", username);
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
}

int main() {
    init_web_app();

    Route route = { .method = "GET", .path = "/check-moderator", .handler = check_moderator_status };
    add_route(route);

    // Placeholder for starting the web server
    return 0;
}