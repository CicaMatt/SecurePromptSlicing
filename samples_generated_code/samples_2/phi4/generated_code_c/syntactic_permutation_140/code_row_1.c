#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "username";
    const char *password = "password";
    const char *database = "dbname";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "SELECT EXISTS(SELECT 1 FROM users WHERE username='testuser')")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    int exists = atoi(row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    if (exists) {
        printf("Username exists.\n");
        return 1;
    } else {
        printf("Username does not exist.\n");
        return 0;
    }
}