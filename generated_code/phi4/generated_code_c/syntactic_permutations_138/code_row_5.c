#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void handle_route(char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return;
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Prepare the query to check if the user is a moderator
    char query[256];
    snprintf(query, sizeof(query), "SELECT role FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "Result set retrieval failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Check the result
    int is_moderator = 0;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] && strcmp(row[0], "moderator") == 0) {
            is_moderator = 1;
        }
    }

    printf("User %s is moderator: %d\n", username, is_moderator);

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    handle_route("example_user");
    return 0;
}


Note: Replace `"localhost"`, `"root"`, `"password"`, and `"database_name"` with your actual database connection details.