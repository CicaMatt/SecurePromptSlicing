#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    const char *method;
    const char *path;
    void (*handler)();
} Route;

void handleModeratorCheck() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql = "SELECT is_moderator FROM users WHERE username=?;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *username = "test_user";
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int is_moderator = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    printf("User '%s' is a moderator: %s\n", username, is_moderator ? "true" : "false");

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void defineRoutes(Route routes[], int *routeCount) {
    routes[*routeCount] = (Route){"GET", "/check-moderator", handleModeratorCheck};
    (*routeCount)++;
}

int main() {
    Route routes[10];
    int routeCount = 0;
    defineRoutes(routes, &routeCount);

    // Simulate a request to the /check-moderator route
    for (int i = 0; i < routeCount; i++) {
        if (strcmp(routes[i].path, "/check-moderator") == 0 && strcmp(routes[i].method, "GET") == 0) {
            routes[i].handler();
        }
    }

    return 0;
}