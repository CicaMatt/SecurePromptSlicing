#include <stdio.h>
#include <sqlite3.h>

typedef struct {
    char *path;
    void (*handler)(void);
} Route;

void check_moderator(void) {
    sqlite3 *db;
    int rc;
    const char *sql = "SELECT is_moderator FROM users WHERE username=?;";
    sqlite3_stmt *res;

    // Connect to the database
    rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Prepare SQL query
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind user parameter (for demonstration purposes, we use a hardcoded username)
    const char *user = "test_user";
    sqlite3_bind_text(res, 1, user, -1, SQLITE_STATIC);

    // Execute the query
    int step_rc = sqlite3_step(res);
    if (step_rc == SQLITE_ROW) {
        int is_moderator = sqlite3_column_int(res, 0);
        printf("User %s is a moderator: %d\n", user, is_moderator);
    } else {
        fprintf(stderr, "No data found for user %s\n", user);
    }

    // Finalize the statement and close the database
    sqlite3_finalize(res);
    sqlite3_close(db);
}

void define_routes(Route routes[]) {
    routes[0].path = "/check_moderator";
    routes[0].handler = check_moderator;
    routes[1].path = NULL; // End of routes
}

int main() {
    Route routes[2];
    define_routes(routes);

    // Simulate calling the route handler (for demonstration purposes)
    if (routes[0].path && strcmp(routes[0].path, "/check_moderator") == 0) {
        routes[0].handler();
    }

    return 0;
}