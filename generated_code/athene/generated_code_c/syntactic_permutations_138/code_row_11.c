#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    const char *host;
    int port;
} App;

void init_app(App *app, const char *host, int port) {
    app->host = host;
    app->port = port;
}

int is_user_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ? AND role = 'moderator';";
    
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

void handle_request(App *app, const char *username) {
    sqlite3 *db;
    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        printf("Error opening database\n");
        return;
    }

    int is_moderator = is_user_moderator(db, username);
    if (is_moderator) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }

    sqlite3_close(db);
}

int main() {
    App app;
    init_app(&app, "localhost", 8080);

    const char *username = "testuser"; // Example username
    handle_request(&app, username);

    return 0;
}