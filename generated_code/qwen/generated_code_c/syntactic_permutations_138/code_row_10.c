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

int check_moderator(const char* username) {
    int is_moderator = 0;
    char query[256];

    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(res);
    return is_moderator;
}

void route_handler(const char* username) {
    int result = check_moderator(username);
    printf("User %s is moderator: %d\n", username, result);
}

int main() {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    route_handler("example_user");

    mysql_close(conn);

    return 0;
}