#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define USERNAME "your_username"
#define PASSWORD "your_password"
#define DATABASE_NAME "your_database_name"

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    if (!mysql_real_connect(conn, "localhost", USERNAME, PASSWORD, DATABASE_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    if (mysql_query(conn, "SELECT is_moderator FROM users WHERE username = 'target_username'")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    int is_moderator = 0;

    while ((row = mysql_fetch_row(res)) != NULL) {
        if (row[0] && atoi(row[0]) == 1) {
            is_moderator = 1;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    if (is_moderator) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}