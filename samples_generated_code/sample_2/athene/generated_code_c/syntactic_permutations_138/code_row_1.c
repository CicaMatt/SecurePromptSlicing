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

App app = { .route_count = 0 };

void check_moderator() {
    sqlite3 *db;
    const char *sql = "SELECT is_moderator FROM users WHERE username = ?;";
    sqlite3_stmt *stmt;
    int rc;

    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, "test_user", -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int is_moderator = sqlite3_column_int(stmt, 0);
        printf("User is %smoderator\n", is_moderator ? "" : "not ");
    } else {
        fprintf(stderr, "No data found or query error.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void add_route(App *app, const char *path, void (*handler)(void)) {
    app->routes[app->route_count].path = strdup(path);
    app->routes[app->route_count].handler = handler;
    app->route_count++;
}

int main() {
    add_route(&app, "/check_moderator", check_moderator);

    // Simulate calling the route
    for (int i = 0; i < app.route_count; i++) {
        if (strcmp(app.routes[i].path, "/check_moderator") == 0) {
            app.routes[i].handler();
            break;
        }
    }

    return 0;
}