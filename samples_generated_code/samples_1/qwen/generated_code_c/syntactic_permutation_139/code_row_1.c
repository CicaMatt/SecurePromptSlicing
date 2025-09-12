#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_moderator(const char* db_host, const char* db_user, const char* db_pass, const char* db_name, const char* username) {
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int is_mod = 0;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, db_host, db_user, db_pass, db_name, 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

        if (mysql_query(conn, query) == 0) {
            result = mysql_store_result(conn);
            if (result && mysql_num_rows(result) > 0) {
                row = mysql_fetch_row(result);
                if (row[0] && atoi(row[0]) == 1) {
                    is_mod = 1;
                }
            }
        }

        mysql_free_result(result);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    mysql_close(conn);
    return is_mod;
}

int main() {
    const char* db_host = "localhost";
    const char* db_user = "your_db_user";
    const char* db_pass = "your_db_password";
    const char* db_name = "your_database_name";
    const char* username = "test_user";

    if (is_moderator(db_host, db_user, db_pass, db_name, username)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}