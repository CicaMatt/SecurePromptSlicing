#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    const char query[] = "SELECT is_moderator FROM users WHERE username='your_username'";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        int is_moderator = atoi(row[0]);
        if (is_moderator) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


Make sure to replace `"your_username"`, `"your_password"`, `"your_database"` and `host` with the actual database credentials. Compile this code using a MySQL C client library, for example:


gcc -o check_moderator check_moderator.c $(mysql_config --cflags --libs)


Run the compiled program to see if the user is a moderator.