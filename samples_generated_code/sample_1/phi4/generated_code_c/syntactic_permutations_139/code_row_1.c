#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "username";  // replace with your username
    const char *password = "password"; // replace with your password
    const char *database = "your_database_name"; // replace with your database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username='your_username'"; // replace 'your_username'
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        int is_moderator = atoi(row[0]);
        printf("%d\n", is_moderator); // Returns 1 for True, 0 for False
    } else {
        printf("0\n"); // User not found or no moderator status defined
    }

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}
