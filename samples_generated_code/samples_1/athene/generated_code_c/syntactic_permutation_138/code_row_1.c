#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    char *path;
    void (*handler)(void);
} Route;

typedef struct {
    Route routes[10];
    int count;
} App;

App app = { .count = 0 };

void add_route(App *app, const char *path, void (*handler)(void)) {
    if (app->count < 10) {
        app->routes[app->count].path = strdup(path);
        app->routes[app->count].handler = handler;
        app->count++;
    }
}

int is_moderator(sqlite3 *db, const char *user) {
    sqlite3_stmt *stmt;
    int rc, result = 0;

    const char *sql = "SELECT is_moderator FROM users WHERE username = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return result;
}

void check_moderator() {
    sqlite3 *db;
    const char *user = "example_user"; // Example user

    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    int result = is_moderator(db, user);

    printf("User is moderator: %d\n", result);

    sqlite3_close(db);
}

int main() {
    add_route(&app, "/check_moderator", check_moderator);

    // Simulate calling the route
    app.routes[0].handler();

    return 0;
}