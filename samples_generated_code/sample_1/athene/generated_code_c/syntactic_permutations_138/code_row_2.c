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

    const char *sql = "SELECT COUNT(*) FROM users WHERE active = 1";
    rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);

    if (rc != SQLITE_OK ) {
       fprintf(stderr, "Failed to select data: %s\n", err_msg);
       sqlite3_free(err_msg);
       sqlite3_close(db);
       exit(1);
    }

    printf("Query executed successfully.\n");
    sqlite3_close(db);
}

int main() {
    // This is a placeholder for the web app framework.
    // In a real application, you would use a C web framework like CivetWeb or others.
    // For this example, we'll just simulate calling the route handler directly.

    handle_request();
    return 0;
}