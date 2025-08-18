#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_request() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql = "SELECT COUNT(*) FROM users";
    rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Query executed successfully.\n");
    }

    sqlite3_close(db);
}

int main() {
    // This is a placeholder for the web app framework.
    // In a real application, you would set up routing and handle HTTP requests here.
    // For this example, we'll just simulate calling the route handler.
    printf("Simulating a request to the defined route.\n");
    handle_request();
    return 0;
}