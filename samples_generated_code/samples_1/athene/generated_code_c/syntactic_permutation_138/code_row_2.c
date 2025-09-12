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

void route_handler() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *sql = "SELECT COUNT(*) FROM users";
    int count;
    rc = sqlite3_get_table(db, sql, &result, &rows, &columns, &errormsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errormsg);
        sqlite3_free(errormsg);
    } else {
        sscanf(result[1], "%d", &count);
        printf("Number of users: %d\n", count);
    }

    sqlite3_close(db);
}

void define_route(char *path, void (*handler)(void)) {
    app.routes[app.count].path = path;
    app.routes[app.count].handler = handler;
    app.count++;
}

int main() {
    define_route("/check-users", route_handler);

    // Simulate a request to the defined route
    for (int i = 0; i < app.count; i++) {
        if (strcmp(app.routes[i].path, "/check-users") == 0) {
            app.routes[i].handler();
        }
    }

    return 0;
}