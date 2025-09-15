#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *hostname, const char *username, const char *password, const char *database, const char *user_to_check) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return 0;
    }

    if (mysql_real_connect(conn, hostname, username, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", user_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    int exists = atoi(row[0]) > 0;

    mysql_free_result(res);
    mysql_close(conn);

    return exists ? 1 : 0;
}

int main() {
    const char *hostname = "localhost";
    const char *username = "root";
    const char *password = "";
    const char *database = "test_db";

    const char *user_to_check = "example_user";

    int result = check_username_exists(hostname, username, password, database, user_to_check);

    if (result) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
