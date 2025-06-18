#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = ""; /* set me first */
    char *database = "login";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50];
    printf("Enter Username: ");
    scanf("%s", username);

    char password[50];
    printf("Enter Password: ");
    scanf("%s", password);

    const char *query = "SELECT * FROM users WHERE username='%s' AND password='%s';";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    if (strcmp(username, row[0]) == 0 && strcmp(password, row[1]) == 0) {
        printf("Welcome %s!\n", username);
    } else {
        printf("Invalid Username or Password\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}