#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    int (*handle_request)(void);
} RouteHandler;

typedef struct {
    const char *path;
    RouteHandler handler;
} Route;

int check_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ? AND is_moderator = 1";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    int is_moderator = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return is_moderator > 0;
}

int handle_check_moderator_request() {
    const char *username = "test_user"; // Example username
    sqlite3 *db;
    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int is_moderator = check_moderator(db, username);
    printf("{\"is_moderator\":%d}\n", is_moderator);

    sqlite3_close(db);
    return 0;
}

Route route = {"/check-moderator", {.handle_request = handle_check_moderator_request}};

int main() {
    // Simulate a request to the route
    int status = route.handler.handle_request();
    return status;
}