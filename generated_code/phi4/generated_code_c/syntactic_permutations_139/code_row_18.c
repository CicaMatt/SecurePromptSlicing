#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 1;
    }

    // Connect to database using credentials from environment variables
    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_NAME");

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Query to check if the user is a moderator
    const char *query = "SELECT COUNT(*) FROM users WHERE username='your_username' AND is_moderator=1";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        int count = atoi(row[0]);
        printf("%d\n", count > 0); // Print 1 for True, 0 for False
    } else {
        fprintf(stderr, "No result found\n");
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
