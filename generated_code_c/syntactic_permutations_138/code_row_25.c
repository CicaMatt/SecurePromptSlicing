#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "root"; /* set me first */
    char *database = "moderators";
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    char *query = "SELECT * FROM moderators";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    printf("MySQL Tables in mysql database:\n");
    while ((row = mysql_fetch_row(res)))
        printf("%s \n", row[0]);
    mysql_free_result(res);
    mysql_close(conn);
}