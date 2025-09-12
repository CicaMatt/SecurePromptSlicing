#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    char *user;
} Request;

typedef struct {
    int status_code;
    char *message;
} Response;

void handle_request(Request *req, Response *res) {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        res->status_code = 500;
        res->message = "Database connection failed";
        return;
    }

    char sql[128];
    snprintf(sql, sizeof(sql), "SELECT is_moderator FROM users WHERE username='%s'", req->user);

    int is_moderator = 0;
    rc = sqlite3_exec(db, sql, (void*)sqlite3_column_int, &is_moderator, NULL);
    if (rc != SQLITE_OK) {
        res->status_code = 500;
        res->message = "Query execution failed";
        sqlite3_close(db);
        return;
    }

    res->status_code = 200;
    res->message = is_moderator ? "User is a moderator" : "User is not a moderator";

    sqlite3_close(db);
}

int main() {
    Request req = {"example_user"};
    Response res = {0, NULL};

    handle_request(&req, &res);

    printf("Status Code: %d\nMessage: %s\n", res.status_code, res.message);

    return 0;
}