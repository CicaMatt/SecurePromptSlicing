#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int checkUsernameExists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_store_result(conn);

    int exists = 0;
    if (res && mysql_num_rows(res) > 0) {
        exists = 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return exists;
}

int main() {
    const char *username = "testuser";
    if (checkUsernameExists(username)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }
    return 0;
}