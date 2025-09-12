#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "app_db"

int is_moderator(const char* username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int result = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        result = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return result;
}

void handle_request(const char* username) {
    int moderator_status = is_moderator(username);
    printf("User %s is a moderator: %d\n", username, moderator_status);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(1);
    }

    handle_request(argv[1]);

    return 0;
}