#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_moderator(const char *user_id) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 0;
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE user_id = '%s'", user_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    int is_mod = 0;
    if (row != NULL && row[0] != NULL) {
        is_mod = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return is_mod;
}

int main() {
    const char *user_id = "12345"; // Example user ID
    if (is_moderator(user_id)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}