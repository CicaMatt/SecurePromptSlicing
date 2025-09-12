#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int checkUsernameExists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int exists = 0;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT 1 FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        exists = 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return exists;
}

int main() {
    const char *username = "testuser";
    int result = checkUsernameExists(username);
    printf("Does the username '%s' exist? %s\n", username, result ? "True" : "False");
    return 0;
}