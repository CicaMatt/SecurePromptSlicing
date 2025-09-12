#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "SELECT * FROM your_table")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\n", row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}