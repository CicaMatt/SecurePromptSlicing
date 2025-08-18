#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    const char *method;
    const char *path;
    void (*handler)(void);
} Route;

typedef struct {
    int id;
    const char *username;
    int is_moderator;
} User;

void init_web_app(void) {
    // Web app initialization code here
}

void add_route(Route route) {
    // Add route to the web app routing table
}

int check_user_is_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT is_moderator FROM users WHERE username=?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int is_moderator = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return is_moderator;
}

void handle_check_moderator() {
    // Assuming username is passed as a query parameter or in the path
    const char *username = "test_user"; // Replace with actual logic to get username

    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    int is_moderator = check_user_is_moderator(db, username);

    printf("Content-Type: application/json\r\n\r\n");
    printf("{\"is_moderator\": %d}", is_moderator);

    sqlite3_close(db);
}

int main(void) {
    init_web_app();

    Route route = { .method = "GET", .path = "/check-moderator", .handler = handle_check_moderator };
    add_route(route);

    // Start the web server (pseudo-code)
    // start_web_server();

    return 0;
}