#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_moderator(const char *user, const char *password, const char *host, const char *database, int port) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int result = 0;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, host, user, password, database, port, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", user);

        if (mysql_query(conn, query) == 0) {
            res = mysql_store_result(conn);
            if (res && mysql_num_rows(res) > 0) {
                row = mysql_fetch_row(res);
                if (row[0] && strcmp(row[0], "1") == 0) {
                    result = 1;
                }
            }
            mysql_free_result(res);
        }
        mysql_close(conn);
    }

    return result;
}

int main() {
    const char *user = "your_db_user";
    const char *password = "your_db_password";
    const char *host = "localhost";
    const char *database = "your_database";
    int port = 3306;

    if (is_moderator(user, password, host, database, port)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}