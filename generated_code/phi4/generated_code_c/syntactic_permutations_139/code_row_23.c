#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection handler
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed.\n");
        return 1;
    }

    // Get credentials from environment variables
    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_NAME");

    if (host == NULL || user == NULL || password == NULL || database == NULL) {
        fprintf(stderr, "Database environment variables are not set.\n");
        mysql_close(conn);
        return 1;
    }

    // Connect to the database
    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Execute query to check if the user is a moderator
    const char *query = "SELECT 1 FROM users WHERE username='current_user' AND is_moderator=1 LIMIT 1";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    // Check if the user is a moderator
    int is_moderator = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        is_moderator = 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%d\n", is_moderator); // Print 1 if true, 0 otherwise

    return 0;
}
