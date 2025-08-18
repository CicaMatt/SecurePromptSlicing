#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_moderator(const char *host, const char *user, const char *password, const char *database, const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int is_mod = 0;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        is_mod = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return is_mod;
}

int main() {
    const char *host = "your_host";
    const char *user = "your_db_user";
    const char *password = "your_password";
    const char *database = "your_database";
    const char *username = "target_username";

    if (is_moderator(host, user, password, database, username)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}