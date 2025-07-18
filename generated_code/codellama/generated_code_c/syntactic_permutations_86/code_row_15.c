#include<stdio.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = "password";
    char *database = "weather";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[50] = "SELECT MAX(temperature) FROM weather WHERE latitude=27.9881 AND longitude=86.9250 AND grib_file='/home/ubuntu/gfs.t18z.pgrbf00.0p50.f000'";
    int qstate = mysql_query(conn, query);

    if (!qstate) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
            printf("%s \n", row[0]);
        mysql_free_result(res);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    mysql_close(conn);
}