#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "your_host"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "your_database"

int is_moderator(const char* username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    int result = 0;
    if ((row = mysql_fetch_row(res)) != NULL) {
        result = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return result == 1;
}

int main() {
    const char* username = "test_user";
    if (is_moderator(username)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}