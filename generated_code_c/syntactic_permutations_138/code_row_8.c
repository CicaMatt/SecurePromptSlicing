#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

int main() {
    int user_id = 123;
    char query[50];
    MYSQL mysql;

    /* Connect to database */
    if (mysql_init(&mysql) == NULL ||
            mysql_real_connect(&mysql, "localhost", "username", "password", "database", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database\n");
        return 1;
    }

    /* Execute query */
    sprintf(query, "SELECT is_moderator FROM users WHERE id=%d", user_id);
    if (mysql_query(&mysql, query)) {
        fprintf(stderr, "Failed to execute query\n");
        return 1;
    }

    /* Fetch result */
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == NULL) {
        fprintf(stderr, "Failed to fetch result\n");
        return 1;
    }

    /* Print result */
    printf("is_moderator: %d\n", *((int *) mysql_fetch_row(result)[0]));

    /* Clean up */
    mysql_free_result(result);
    mysql_close(&mysql);

    return 0;
}