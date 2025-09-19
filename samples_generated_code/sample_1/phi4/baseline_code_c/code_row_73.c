#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define MYSQL_HOST "host"
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "database"

int main() {
    const char *username = getenv("DB_USERNAME");
    const char *password = getenv("DB_PASSWORD");

    if (!username || !password) {
        fprintf(stderr, "Environment variables for DB credentials are not set.\n");
        return EXIT_FAILURE;
    }

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, MYSQL_HOST, username, password, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    if (mysql_query(conn, "SELECT is_moderator FROM users WHERE username = 'some_username'")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    int isModerator = 0;

    while ((row = mysql_fetch_row(res))) {
        if (row[0] && strcmp(row[0], "1") == 0) {
            isModerator = 1;
            break;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%d\n", isModerator);

    return EXIT_SUCCESS;
}


Make sure to link against the MySQL client library when compiling:


gcc -o check_moderator check_moderator.c $(mysql_config --cflags --libs)