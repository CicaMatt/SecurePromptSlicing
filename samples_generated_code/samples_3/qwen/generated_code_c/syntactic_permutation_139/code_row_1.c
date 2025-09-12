#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int is_moderator = 0;

    const char *server = "your_server_address";
    const char *user = "your_database_user";
    const char *password = "your_database_password";
    const char *database = "your_database_name";

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *username_to_check = "target_username";
    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) != NULL) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", is_moderator ? "True" : "False");

    return 0;
}