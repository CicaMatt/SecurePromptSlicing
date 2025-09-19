#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int isModerator(const char *user) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *userDB = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, userDB, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", user);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
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

int main() {
    const char *username = "testuser";
    if (isModerator(username)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}