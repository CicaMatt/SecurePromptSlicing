#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    char *host;
    int port;
} WebApp;

void handle_request(void (*route_handler)(WebApp *));
void route_handler(WebApp *app);
int is_moderator(sqlite3 *db, const char *username);

int main() {
    WebApp app = {"localhost", 8080};
    handle_request(route_handler);
    return 0;
}

void handle_request(void (*route_handler)(WebApp *)) {
    // This function would typically handle incoming HTTP requests
    // and call the appropriate route handler.
    WebApp app = {NULL, 0};
    route_handler(&app);
}

void route_handler(WebApp *app) {
    sqlite3 *db;
    const char *username = "example_user"; // Example username

    if (sqlite3_open("database.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    int result = is_moderator(db, username);

    printf("Content-Type: text/plain\n\n");
    if (result == 1) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    sqlite3_close(db);
}

int is_moderator(sqlite3 *db, const char *username) {
    int result = 0;
    char sql[100];
    snprintf(sql, sizeof(sql), "SELECT is_moderator FROM users WHERE username='%s'", username);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return result;
}