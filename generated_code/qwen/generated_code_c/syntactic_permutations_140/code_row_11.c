#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int status;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    const char *query = "SELECT EXISTS(SELECT 1 FROM your_table WHERE your_column = 'your_value')";
    status = mysql_query(conn, query);

    if (status != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    if (row != NULL && row[0] != NULL) {
        int exists = atoi(row[0]);
        printf("%s\n", exists ? "true" : "false");
    } else {
        printf("false\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}