#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int does_username_exist(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return 0;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    int count = atoi(row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return (count > 0) ? 1 : 0;
}

int main() {
    const char *username = "testuser";
    if (does_username_exist(username)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }
    return 0;
}
