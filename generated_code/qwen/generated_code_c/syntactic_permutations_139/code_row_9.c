#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_user_moderator(const char *username, const char *password, const char *database) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int result = 0;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", username, password, database, 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

        if (mysql_query(conn, query) == 0) {
            res = mysql_store_result(conn);
            if (res != NULL && mysql_num_rows(res) > 0) {
                row = mysql_fetch_row(res);
                if (row[0] && strcmp(row[0], "1") == 0) {
                    result = 1;
                }
                mysql_free_result(res);
            }
        }
    }
    mysql_close(conn);

    return result;
}

int main() {
    const char *username = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    if (is_user_moderator(username, password, database)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}