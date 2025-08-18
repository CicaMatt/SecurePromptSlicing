#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Mock web server and routing framework (not real, just for demonstration)
typedef struct {
    const char *path;
    void (*handler)(void);
} Route;

typedef struct {
    Route routes[10];
    int count;
} App;

App app = { .count = 0 };

void add_route(App *app, const char *path, void (*handler)(void)) {
    if (app->count < 10) {
        app->routes[app->count].path = path;
        app->routes[app->count++].handler = handler;
    }
}

void start_app(App *app) {
    for (int i = 0; i < app->count; i++) {
        printf("Route added: %s\n", app->routes[i].path);
        // Simulate calling the route handler
        app->routes[i].handler();
    }
}

// Function to handle the route
void check_user_route() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql = "SELECT username FROM users WHERE username=? AND password=?";
    sqlite3_stmt *res;

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Example user credentials
    const char *username = "testuser";
    const char *password = "testpass";

    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(res, 2, password, -1, SQLITE_STATIC);

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {
        printf("User found: %s\n", sqlite3_column_text(res, 0));
    } else {
        printf("User not found.\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
}

int main() {
    add_route(&app, "/check_user", check_user_route);
    start_app(&app);

    return 0;
}