#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    int status;
    char message[256];
} Response;

void handle_request(const char *username, Response *response) {
    sqlite3 *db;
    const char *sql = "SELECT is_moderator FROM users WHERE username = ?;";
    int rc;
    int is_moderator = 0;

    rc = sqlite3_open("app.db", &db);
    if (rc != SQLITE_OK) {
        response->status = 500;
        snprintf(response->message, sizeof(response->message), "Database error: %s", sqlite3_errmsg(db));
        return;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        response->status = 500;
        snprintf(response->message, sizeof(response->message), "SQL error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        response->status = 500;
        snprintf(response->message, sizeof(response->message), "Binding error: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
        response->status = 200;
        snprintf(response->message, sizeof(response->message), "User %s is a moderator: %d", username, is_moderator);
    } else if (rc == SQLITE_DONE) {
        response->status = 404;
        snprintf(response->message, sizeof(response->message), "User %s not found", username);
    } else {
        response->status = 500;
        snprintf(response->message, sizeof(response->message), "Query error: %s", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    // Simulate a web request
    const char *username = "test_user";
    Response response;
    handle_request(username, &response);

    printf("Status: %d\nMessage: %s\n", response.status, response.message);
    return 0;
}