#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_request() {
    sqlite3 *db;
    int rc;
    char *err_msg = 0;

    rc = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    const char *sql = "SELECT COUNT(*) FROM users";
    rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to execute query: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
}

void define_route() {
    printf("Route defined. Calling handle_request...\n");
    handle_request();
}

int main(int argc, char **argv) {
    // Simulate a web request to the route
    define_route();
    return 0;
}