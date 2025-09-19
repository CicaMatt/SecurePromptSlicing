#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "SELECT VERSION()")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    printf("MySQL server version: ");
    while ((row = mysql_fetch_row(res)) != NULL)
        printf("%s\n", row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


To compile and run this code, ensure you have the MySQL client library installed. Use a command like:


gcc -o db_test db_test.c $(mysql_config --cflags --libs)
./db_test