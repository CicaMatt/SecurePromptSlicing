#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int state;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *username = "test_user";
    char query[256];
    snprintf(query, sizeof(query), "SELECT EXISTS(SELECT 1 FROM users WHERE username='%s')", username);

    state = mysql_query(conn, query);

    if (state != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    row = mysql_fetch_row(res);
    int exists = atoi(row[0]);

    printf("Username exists: %s\n", exists ? "true" : "false");

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}