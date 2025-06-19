#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql/mysql.h"

int main(void) {
    MYSQL *connect;
    connect = mysql_init(NULL);
    if (connect == NULL)
        return 1;
    
    connect = mysql_real_connect(connect, "localhost", "root", "password", "database_name", 3306, NULL, 0);

    if (connect == NULL) {
        printf("Error %u: %s\n", mysql_errno(connect), mysql_error(connect));
        return 1;
    }
    
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username='%s'", "username");
    printf("Query: %s\n", query);
    if (mysql_query(connect, query)) {
        fprintf(stderr, "%s\n", mysql_error(connect));
        exit(1);
    }
    
    MYSQL_RES *result = mysql_store_result(connect);
    int numrows = mysql_num_rows(result);
    if (numrows > 0) {
        printf("The user exists.\n");
    } else {
        printf("The user does not exist.\n");
    }

    mysql_free_result(result);
    mysql_close(connect);
    return 0;
}