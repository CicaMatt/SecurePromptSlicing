#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[50] = "SELECT * FROM users WHERE name='moderator'";
    int retval = mysql_query(conn, query);
    if (retval) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    printf("Result: %lu\n", mysql_num_rows(res));

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}