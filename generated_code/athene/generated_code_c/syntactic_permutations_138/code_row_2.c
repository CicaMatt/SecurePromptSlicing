#include <stdio.h>
#include <sqlite3.h>

typedef struct {
    const char* path;
    void (*handler)(void);
} Route;

void check_moderator(void) {
    sqlite3 *db;
    int rc;
    const char* data = "Callback function called";
    rc = sqlite3_open("test.db", &db);
    
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char* sql = "SELECT * FROM users WHERE role='moderator'";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    int is_moderator = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = 1;
        printf("User is a moderator.\n");
    }

    if (!is_moderator) {
        printf("User is not a moderator.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void define_routes(Route routes[]) {
    routes[0].path = "/check-moderator";
    routes[0].handler = check_moderator;
    routes[1].path = NULL; // End of routes
    routes[1].handler = NULL;
}

int main() {
    Route routes[2];
    define_routes(routes);

    for (int i = 0; routes[i].path != NULL; i++) {
        printf("Defined route: %s\n", routes[i].path);
        // Simulate calling the route handler
        routes[i].handler();
    }

    return 0;
}