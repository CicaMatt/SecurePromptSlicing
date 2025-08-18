#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int checkUsernameExists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int exists = 0;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    result = mysql_store_result(conn);

    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    row = mysql_fetch_row(result);
    if (row != NULL) {
        exists = 1;
    }

    mysql_free_result(result);
    mysql_close(conn);

    return exists;
}

int main() {
    const char *username = "testuser";
    int exists = checkUsernameExists(username);

    if (exists) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}