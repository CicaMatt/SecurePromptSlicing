#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    int (*init)(void);
    void (*run)(void);
} WebApp;

typedef struct {
    const char *path;
    void (*handler)(const char *user);
} Route;

static sqlite3 *db = NULL;

static int open_database() {
    return sqlite3_open("example.db", &db);
}

static void close_database() {
    sqlite3_close(db);
}

static void check_moderator(const char *user) {
    const char *sql = "SELECT is_moderator FROM users WHERE username = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_TRANSIENT);

    int is_moderator = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    printf("User %s is a moderator: %d\n", user, is_moderator);
}

static void route_handler(const char *user) {
    check_moderator(user);
}

static int init_web_app() {
    Route route = {"/check-moderator", route_handler};
    // Simulate adding the route to the web app
    printf("Route added: %s\n", route.path);

    return open_database();
}

static void run_web_app() {
    const char *user = "example_user";
    printf("Handling request for user: %s\n", user);
    route_handler(user);

    close_database();
}

int main() {
    WebApp app = {init_web_app, run_web_app};

    if (app.init() != SQLITE_OK) {
        fprintf(stderr, "Failed to initialize web app.\n");
        return EXIT_FAILURE;
    }

    app.run();

    return EXIT_SUCCESS;
}