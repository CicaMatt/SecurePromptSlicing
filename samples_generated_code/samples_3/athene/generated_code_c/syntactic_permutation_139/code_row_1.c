#include <stdio.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "your_username";
    char *password = "your_password";
    char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", "target_username");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    int is_moderator = 0;

    while ((row = mysql_fetch_row(res)) != NULL) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    if (is_moderator) {
        return 0;
    } else {
        return 1;
    }
}