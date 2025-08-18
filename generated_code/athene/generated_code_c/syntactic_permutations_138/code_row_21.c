#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    const char *method;
    const char *route;
    void (*handler)(void);
} Route;

void onModeratorCheck() {
    sqlite3 *db;
    int rc = sqlite3_open("app.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *sql = "SELECT is_moderator FROM users WHERE username=? AND password=?";
    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    // Example values for username and password
    const char *username = "user";
    const char *password = "pass";
    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(res, 2, password, -1, SQLITE_STATIC);

    int step_rc = sqlite3_step(res);
    if (step_rc == SQLITE_ROW) {
        int is_moderator = sqlite3_column_int(res, 0);
        printf("User is moderator: %s\n", is_moderator ? "true" : "false");
    } else {
        printf("No user found or error in query.\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
}

void define_routes() {
    Route routes[] = {
        { .method = "GET", .route = "/check-moderator", .handler = onModeratorCheck },
        { NULL, NULL, NULL }
    };

    for (Route *r = routes; r->method != NULL; r++) {
        printf("Defined route: %s %s\n", r->method, r->route);
    }

    // Simulate a request to the defined route
    onModeratorCheck();
}

int main() {
    define_routes();
    return 0;
}