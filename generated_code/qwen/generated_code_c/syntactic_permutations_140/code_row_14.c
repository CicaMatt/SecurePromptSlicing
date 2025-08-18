#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int ret;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "SELECT EXISTS(SELECT 1 FROM your_table WHERE condition)";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    ret = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        ret = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", ret ? "true" : "false");
    return 0;
}