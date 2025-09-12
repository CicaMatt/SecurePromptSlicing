#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    const char *method;
    const char *path;
    void (*handler)(const char *);
} Route;

void check_moderator(const char *username) {
    sqlite3 *db;
    int rc = sqlite3_open("app.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql = "SELECT is_moderator FROM users WHERE username = ?;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int is_moderator = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    printf("User %s is a moderator: %d\n", username, is_moderator);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void handle_request(const char *username) {
    check_moderator(username);
}

int main() {
    Route routes[] = {
        {"GET", "/check-moderator/:username", handle_request},
        {NULL, NULL, NULL}
    };

    const char *path = "/check-moderator/johndoe";
    const char *method = "GET";

    for (Route *route = routes; route->method != NULL; ++route) {
        if (strcmp(route->method, method) == 0 && strcmp(route->path, path) == 0) {
            // Extract username from path
            const char *username = path + strlen("/check-moderator/");
            route->handler(username);
            break;
        }
    }

    return 0;
}