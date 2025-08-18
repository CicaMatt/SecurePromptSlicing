#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(MYSQL *conn, const char *username) {
    int exists = 0;
    char query[256];
    MYSQL_RES *res;
    MYSQL_ROW row;

    sprintf(query, "SELECT COUNT(*) FROM users WHERE username='%s'", mysql_real_escape_string(conn, (char*)username, strlen(username)));
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    if (row[0] && atoi(row[0]) > 0) {
        exists = 1;
    }

    mysql_free_result(res);
    return exists;
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *username = "testuser";
    int exists = check_username_exists(conn, username);

    if (exists) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    mysql_close(conn);
    return 0;
}