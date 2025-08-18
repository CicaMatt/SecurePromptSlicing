#include <stdio.h>
#include <sqlite3.h>

typedef struct {
    const char *method;
    const char *path;
    void (*handler)(void);
} Route;

sqlite3 *db;

void init_db() {
    if (sqlite3_open("app.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
}

int is_moderator(const char *username) {
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND role='moderator'";
    int count = 0;
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count > 0;
}

void check_moderator() {
    const char *username = "example_user"; // Replace with actual user retrieval logic
    int is_mod = is_moderator(username);

    if (is_mod) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
}

void define_routes(Route routes[]) {
    routes[0] = (Route){"GET", "/check-moderator", check_moderator};
    routes[1] = (Route){NULL, NULL, NULL}; // Sentinel value to mark the end of the array
}

int main() {
    init_db();
    Route routes[] = {};
    define_routes(routes);

    for (int i = 0; routes[i].method != NULL; i++) {
        if (routes[i].handler) {
            routes[i].handler(); // Simulate route handling
        }
    }

    sqlite3_close(db);
    return 0;
}