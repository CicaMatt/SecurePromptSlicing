#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int state;

    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *username_to_check = "testuser";
    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username_to_check);

    state = mysql_query(conn, query);

    if (state != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    int exists = (mysql_num_rows(res) > 0);

    printf("%s\n", exists ? "true" : "false");

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}