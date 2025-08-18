#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    int (*init)(void);
    void (*run)(void);
} WebApp;

typedef struct {
    const char *route;
    void (*handler)(void);
} Route;

int is_moderator(sqlite3 *db, const char *user) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND role='moderator'";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_TRANSIENT);

    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return result > 0;
}

void handle_route() {
    sqlite3 *db;
    const char *user = "example_user"; // This should come from the request
    if (sqlite3_open("app.db", &db) == SQLITE_OK) {
        int is_mod = is_moderator(db, user);
        printf("Content-Type: application/json\r\n\r\n");
        printf("{\"is_moderator\": %d}", is_mod);
        sqlite3_close(db);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Database connection failed");
    }
}

void init_app() {
    Route routes[] = {{"GET /check-moderator", handle_route}};
    // Simulate route registration
    for (size_t i = 0; i < sizeof(routes) / sizeof(Route); ++i) {
        printf("Route registered: %s\n", routes[i].route);
    }
}

void run_app() {
    init_app();
    // Simulate web server running
    printf("Web app is running...\n");
    handle_route(); // This would normally be called when the route is hit
}

int main() {
    WebApp app = {init_app, run_app};
    app.run();
    return 0;
}