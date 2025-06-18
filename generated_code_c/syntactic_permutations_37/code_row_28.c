#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "mydatabase"

int main(void) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *query = "SELECT username, password FROM users WHERE username='%s' AND password='%s'"

    int status = 0;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        status = 1;
    } else {
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (strcmp(row[0], "username") == 0 && strcmp(row[1], "password") == 0) {
            status = 2;
        } else {
            status = 3;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    if (status == 1) {
        printf("Error: %s\n", mysql_error(conn));
    } else if (status == 2) {
        printf("Login Successful!\n");
    } else if (status == 3) {
        printf("Can't Login, Incorrect Username or Password.\n");
    } else {
        printf("Internal Server Error.\n");
    }

    return status;
}