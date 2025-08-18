#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "your_database_name"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int check_if_moderator(const char* username) {
    int is_moderator = 0;
    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res)) != NULL) {
        is_moderator = atoi(row[0]);
    }
    mysql_free_result(res);

    return is_moderator;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char* username = "test_user"; // This should be dynamically set based on the request
    int result = check_if_moderator(username);

    if (result == -1) {
        printf("Error checking moderator status.\n");
    } else if (result == 0) {
        printf("User is not a moderator.\n");
    } else {
        printf("User is a moderator.\n");
    }

    mysql_close(conn);
    return 0;
}