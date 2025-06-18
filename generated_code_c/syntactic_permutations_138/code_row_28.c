#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

int main(void) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char *query = "SELECT isModerator FROM users WHERE username = 'JohnDoe'";
    int queryResult = mysql_query(conn, query);
    if (queryResult) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    int numRows = mysql_num_rows(result);
    if (numRows > 0) {
        printf("User is a moderator\n");
    } else {
        printf("User is not a moderator\n");
    }

    return EXIT_SUCCESS;
}