#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int ret = 0;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *username = "test_user";
    char query[256];
    snprintf(query, sizeof(query), "SELECT EXISTS(SELECT 1 FROM users WHERE username='%s') AS user_exists", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row[0] && strcmp(row[0], "1") == 0) {
        ret = 1; // Username exists
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", ret ? "true" : "false");
    return 0;
}