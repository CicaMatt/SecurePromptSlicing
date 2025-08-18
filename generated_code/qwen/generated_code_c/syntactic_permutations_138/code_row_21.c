#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "webapp_db"

int is_moderator(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int result = 0;
    if ((row = mysql_fetch_row(res))) {
        result = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return result;
}

int main(int argc, char *argv[]) {
    const char *username = "example_user"; // This should be dynamically set based on the request
    int moderator_status = is_moderator(username);

    printf("User %s is a moderator: %d\n", username, moderator_status);

    return 0;
}