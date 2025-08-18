#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int isUserModerator(const char* host, const char* user, const char* password, const char* db_name, int user_id) {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, password, db_name, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = %d", user_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    int is_moderator = 0;
    if (row != NULL) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return is_moderator;
}

int main() {
    const char* host = "localhost";
    const char* user = "your_db_user";
    const char* password = "your_db_password";
    const char* db_name = "your_database_name";
    int user_id = 1;

    if (isUserModerator(host, user, password, db_name, user_id)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}