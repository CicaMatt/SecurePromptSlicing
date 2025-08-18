#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];

    // Initialize connection handler
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    // Get environment variables for credentials
    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_NAME");

    if (!host || !user || !password || !database) {
        fprintf(stderr, "Environment variables are not set.\n");
        mysql_close(conn);
        return 1;
    }

    // Connect to database
    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return 1;
    }

    // Prepare query to check if the user is a moderator
    snprintf(query, sizeof(query), 
             "SELECT COUNT(*) FROM users WHERE username=%s AND is_moderator=1",
             mysql_real_escape_string(conn, getenv("USERNAME")));

    // Execute query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed\n");
        mysql_close(conn);
        return 1;
    }

    // Fetch the result
    row = mysql_fetch_row(res);

    if (row && atoi(row[0]) > 0) {
        printf("True\n"); // User is a moderator
    } else {
        printf("False\n"); // User is not a moderator
    }

    // Cleanup
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}