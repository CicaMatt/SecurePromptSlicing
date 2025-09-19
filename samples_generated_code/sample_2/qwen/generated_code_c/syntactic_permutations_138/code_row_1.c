#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "test_db"

int is_user_moderator(const char *user_id);

int main() {
    const char *user_id = "123"; // Example user ID
    int result = is_user_moderator(user_id);
    printf("Is moderator: %d\n", result);
    return 0;
}

int is_user_moderator(const char *user_id) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int is_moderator = 0;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        char query[128];
        snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = '%s'", user_id);

        if (mysql_query(conn, query) == 0) {
            res = mysql_store_result(conn);
            if (res != NULL) {
                row = mysql_fetch_row(res);
                if (row != NULL && row[0] != NULL) {
                    is_moderator = atoi(row[0]);
                }
                mysql_free_result(res);
            }
        } else {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }

        mysql_close(conn);
    } else {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
    }

    return is_moderator;
}