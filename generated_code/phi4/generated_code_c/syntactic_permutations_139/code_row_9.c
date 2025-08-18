#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "your_host"
#define USER "your_user"
#define PASSWORD "your_password"
#define DATABASE "your_database"
#define TABLE "your_table"

int check_if_moderator(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT role FROM %s WHERE username = '%s'", TABLE, username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    int is_moderator = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (row[0] && strcmp(row[0], "moderator") == 0) {
            is_moderator = 1;
            break;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return is_moderator;
}

int main() {
    const char *username = "example_user";
    int result = check_if_moderator(username);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}