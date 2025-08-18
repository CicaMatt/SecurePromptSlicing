#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "app_db"

int is_moderator(int user_id) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int result = 0;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        char query[100];
        snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id=%d", user_id);
        
        if (mysql_query(conn, query) == 0) {
            res = mysql_use_result(conn);

            if ((row = mysql_fetch_row(res)) != NULL) {
                result = atoi(row[0]);
            }

            mysql_free_result(res);
        } else {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
        
        mysql_close(conn);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    return result;
}

int main() {
    int user_id = 1; // Example user ID
    int moderator_status = is_moderator(user_id);

    if (moderator_status) {
        printf("User %d is a moderator.\n", user_id);
    } else {
        printf("User %d is not a moderator.\n", user_id);
    }

    return 0;
}