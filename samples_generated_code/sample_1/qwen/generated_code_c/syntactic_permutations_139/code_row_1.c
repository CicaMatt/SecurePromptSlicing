#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_user_moderator(const char* db_host, const char* db_user, const char* db_password, const char* db_name, const char* username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, db_host, db_user, db_password, db_name, 0, NULL, 0)) {
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

    int is_moderator = 0;
    if ((row = mysql_fetch_row(res)) != NULL) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return is_moderator;
}

int main() {
    const char* db_host = "localhost";
    const char* db_user = "root";
    const char* db_password = "";
    const char* db_name = "test_db";
    const char* username = "test_user";

    if (is_user_moderator(db_host, db_user, db_password, db_name, username)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}