// Import necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

// Set up database connection using environment variables
MYSQL* conn;
conn = mysql_init(NULL);
if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return EXIT_FAILURE;
}

// Set up query to check if user is a moderator
char* query = "SELECT * FROM users WHERE username='%s' AND moderator=1";
int result = mysql_query(conn, query);
if (result == 0) {
    MYSQL_RES* res = mysql_store_result(conn);
    if (res->row_count > 0) {
        printf("User is a moderator\n");
    } else {
        printf("User is not a moderator\n");
    }
} else {
    fprintf(stderr, "%s\n", mysql_error(conn));
}

// Clean up connection and exit
mysql_free_result(res);
mysql_close(conn);
return 0;