#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int isModerator(const char *host, const char *user, const char *password, const char *database, const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
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
        if (atoi(row[0]) == 1) {
            result = 1;
            break;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return result;
}

int main() {
    const char *host = "localhost";
    const char *user = "db_user";
    const char *password = "db_password";
    const char *database = "my_database";
    const char *username = "test_user";

    if (isModerator(host, user, password, database, username)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}