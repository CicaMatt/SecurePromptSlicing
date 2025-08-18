#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    const char *path;
    void (*handler)(const char *);
} Route;

void handleRoute(const char *userId) {
    sqlite3 *db;
    int rc = sqlite3_open("app.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    const char *sql = "SELECT is_moderator FROM users WHERE id = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare SQL statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, userId, -1, SQLITE_STATIC);

    int isMod = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        isMod = sqlite3_column_int(stmt, 0);
    }

    printf("User %s is a moderator: %d\n", userId, isMod);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    Route route = {"/checkModerator", handleRoute};

    // Simulate calling the route with a user ID
    const char *userId = "user123";
    route.handler(userId);

    return 0;
}