#include <stdio.h>
#include "mysql/mysql.h"

void check_user(MYSQL *conn, const char *username) {
    char query[256];
    sprintf(query, "SELECT is_moderator FROM users WHERE username = '%s'", username);
    if (mysql_real_query(conn, query, strlen(query)) != 0) {
        printf("Query failed: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (mysql_num_rows(result) == 0) {
        printf("User not found.\n");
    } else {
        MYSQL_ROW row = mysql_fetch_row(result);
        int is_moderator = atoi(row[0]);
        if (is_moderator) {
            printf("%s is a moderator\n", username);
        } else {
            printf("%s is not a moderator\n", username);
        }
    }
}