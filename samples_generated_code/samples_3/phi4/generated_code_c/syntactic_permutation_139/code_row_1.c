#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "your_username"; // Replace with your username variable
    const char *password = "your_password"; // Replace with your password variable
    const char *database = "your_database_name"; // Replace with your database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    const char *query = "SELECT role FROM users WHERE username='specific_username'"; // Replace 'specific_username' with the variable holding the username

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    int isModerator = 0; // Default to False
    while ((row = mysql_fetch_row(res))) {
        if (row[0] && strcmp(row[0], "moderator") == 0) {
            isModerator = 1; // True
        }
    }

    printf("%d\n", isModerator);

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}