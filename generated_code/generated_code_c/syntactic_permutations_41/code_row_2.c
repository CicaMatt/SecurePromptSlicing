#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

int main(void) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "admin";  // set me first
    char *database = "mydb";   // set me first
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, "SELECT username, email, ssn FROM users WHERE id = 12345")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    printf("Username: %s  Email: %s SSN: %s", row[0], row[1], row[2]);
    mysql_free_result(res);
    mysql_close(conn);
}