#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "your_host"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "your_database"

int checkIfUserIsModerator(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);
    int isModerator = 0;

    while ((row = mysql_fetch_row(res))) {
        if (row[0] && strcmp(row[0], "1") == 0) {
            isModerator = 1;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return isModerator;
}

int main() {
    const char *username = "example_user";

    int result = checkIfUserIsModerator(username);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}