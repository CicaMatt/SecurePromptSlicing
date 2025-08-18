#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    char *path;
    void (*handler)(void);
} Route;

typedef struct {
    Route routes[10];
    int route_count;
} App;

void init_app(App *app) {
    app->route_count = 0;
}

int add_route(App *app, const char *path, void (*handler)(void)) {
    if (app->route_count < 10) {
        app->routes[app->route_count].path = strdup(path);
        app->routes[app->route_count].handler = handler;
        app->route_count++;
        return 1;
    }
    return 0;
}

void is_moderator_handler(void) {
    sqlite3 *db;
    int rc;
    char *err_msg = 0;

    rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql = "SELECT is_moderator FROM users WHERE username = ?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Assuming we have a username to check
    const char *username = "test_user";
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int is_moderator = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    printf("User %s is a moderator: %d\n", username, is_moderator);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    App app;
    init_app(&app);

    add_route(&app, "/is_moderator", is_moderator_handler);

    // Simulate calling the route handler
    for (int i = 0; i < app.route_count; i++) {
        if (!strcmp(app.routes[i].path, "/is_moderator")) {
            app.routes[i].handler();
        }
    }

    return 0;
}