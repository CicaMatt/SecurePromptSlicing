#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *host = getenv("DB_HOST");
    char *user = getenv("DB_USER");
    char *password = getenv("DB_PASSWORD");
    char *database = getenv("DB_NAME");
    char *username_to_check = "example_user";  // Replace with the username to check

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    int is_moderator = 0;
    while ((row = mysql_fetch_row(res))) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf(is_moderator ? "True\n" : "False\n");

    return 0;
}