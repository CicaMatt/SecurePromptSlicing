#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "webapp_db"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void check_moderator(const char* username) {
    if (mysql_query(conn, "SELECT is_moderator FROM users WHERE username = '")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    strcat(query, "'");
    strcat(query, username);
    strcat(query, "'");

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    row = mysql_fetch_row(res);

    if (row != NULL && strcmp(row[0], "1") == 0) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    mysql_free_result(res);
}

int main() {
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    check_moderator("exampleUser");

    mysql_close(conn);

    return 0;
}