#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "mydatabase"

MYSQL *conn;

int check_moderator(char *username) {
    int is_moderator = 0;
    char query[256];

    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL && strcmp(row[0], "1") == 0) {
        is_moderator = 1;
    }

    mysql_free_result(result);
    return is_moderator;
}

int main() {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[] = "testuser";
    int is_moderator = check_moderator(username);

    if (is_moderator == -1) {
        printf("Error checking moderator status.\n");
    } else if (is_moderator) {
        printf("%s is a moderator.\n", username);
    } else {
        printf("%s is not a moderator.\n", username);
    }

    mysql_close(conn);

    return 0;
}