#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int userExists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int ret = 0;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        ret = 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return ret;
}

int main() {
    const char *username = "testuser";
    if (userExists(username)) {
        printf("User exists.\n");
    } else {
        printf("User does not exist.\n");
    }
    return 0;
}