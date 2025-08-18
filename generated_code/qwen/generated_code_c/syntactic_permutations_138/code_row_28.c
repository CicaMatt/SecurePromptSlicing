#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "webapp"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int is_moderator(char *username) {
    int result = 0;
    char query[256];

    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_use_result(conn);
    if ((row = mysql_fetch_row(res))) {
        result = atoi(row[0]);
    }

    mysql_free_result(res);
    return result;
}

void route_handler(char *username) {
    int moderator_status = is_moderator(username);
    printf("Content-Type: text/plain\n\n");
    printf("User %s is a moderator: %s\n", username, moderator_status ? "true" : "false");
}

int main(int argc, char **argv) {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Simulating a web request with username "testuser"
    route_handler("testuser");

    mysql_close(conn);
    return 0;
}