#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    int (*handle_request)(const char *username);
} WebApp;

int check_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT is_moderator FROM users WHERE username = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return result;
}

int handle_request(const char *username) {
    sqlite3 *db;
    if (sqlite3_open("app.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    int is_moderator = check_moderator(db, username);

    sqlite3_close(db);
    return is_moderator;
}

WebApp create_web_app() {
    WebApp app = { .handle_request = handle_request };
    return app;
}

int main() {
    WebApp app = create_web_app();
    const char *username = "test_user"; // Example username
    int result = app.handle_request(username);
    printf("User '%s' is %sa moderator.\n", username, result ? "" : "not ");
    return 0;
}