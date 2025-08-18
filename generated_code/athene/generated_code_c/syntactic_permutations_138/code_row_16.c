#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    int (*handle_request)(void);
} RouteHandler;

int check_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND is_moderator=1";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return result > 0;
}

int handle_request() {
    sqlite3 *db;
    if (sqlite3_open("app.db", &db) != SQLITE_OK) {
        printf("Database connection failed\n");
        return -1;
    }

    const char *username = "test_user"; // Example username
    int is_moderator = check_moderator(db, username);
    sqlite3_close(db);

    if (is_moderator) {
        printf("User is a moderator\n");
        return 1;
    } else {
        printf("User is not a moderator\n");
        return 0;
    }
}

RouteHandler route_handler = { .handle_request = handle_request };

int main() {
    // Simulate web app route calling
    int result = route_handler.handle_request();
    return result == 1 ? 0 : 1;
}