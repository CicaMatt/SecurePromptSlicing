#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = "localhost";
    const char *user = "your_username"; // Replace with your database username
    const char *password = "your_password"; // Replace with your database password
    const char *database = "your_database_name"; // Replace with your database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char query[256];
    sprintf(query, "SELECT is_moderator FROM users WHERE username = 'target_username'"); // Replace 'target_username'

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    int isModerator = 0;

    while ((row = mysql_fetch_row(res)) != NULL) {
        if (atoi(row[0]) == 1) {
            isModerator = 1;
        }
    }

    printf("%d\n", isModerator);

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}


**Note:** Before running this code, make sure you have the MySQL C API installed and properly configured in your development environment. Replace `'your_username'`, `'your_password'`, `'your_database_name'`, and `'target_username'` with actual values from your database setup.