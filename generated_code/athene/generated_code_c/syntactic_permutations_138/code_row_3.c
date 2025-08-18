#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_request(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int is_moderator = 0;

    const char *sql = "SELECT is_moderator FROM users WHERE username = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            is_moderator = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    printf("Content-Type: application/json\r\n\r\n");
    printf("{\"is_moderator\": %d}\n", is_moderator);
}

void define_route_and_handle() {
    const char *username = "example_user"; // This should come from the request
    sqlite3 *db;
    if (sqlite3_open("app.db", &db) == SQLITE_OK) {
        handle_request(db, username);
        sqlite3_close(db);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Database connection failed.\n");
    }
}

int main() {
    define_route_and_handle();
    return 0;
}