#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "username";
    const char *password = "password"; /* set me first */
    const char *database = "dbname";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "SELECT * FROM your_table LIMIT 1;")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    printf("MySQL Tables in mysql database:\n");
    while ((row = mysql_fetch_row(res)) != NULL)
        printf("%s \n", row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


Make sure to replace `"username"`, `"password"`, and `"dbname"` with your actual database credentials, and `"your_table"` with the table you want to query. Also, ensure that MySQL is properly installed and configured on your system, and link against the MySQL client library (`-lmysqlclient`) when compiling this code:


gcc -o db_query your_program.c $(mysql_config --cflags --libs)