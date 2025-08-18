#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *username_to_check = "test_user";
    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int user_exists = 0;
    if ((row = mysql_fetch_row(res)) != NULL) {
        user_exists = 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", user_exists ? "true" : "false");

    return 0;
}