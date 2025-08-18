#include <stdio.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int found = 0;

    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";
    const char *username_to_check = "test_user";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        found = 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", found ? "true" : "false");

    return 0;
}