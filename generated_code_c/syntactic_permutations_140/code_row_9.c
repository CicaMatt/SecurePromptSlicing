#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0)) {
        printf("Connection failed");
        return 1;
    }

    // Execute query
    char *query = "SELECT * FROM table_name";
    if (mysql_query(conn, query)) {
        printf("Query failed: %s\n", mysql_error(conn));
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        int num_rows = mysql_num_rows(result);
        printf("%d row(s) returned\n", num_rows);
        mysql_free_result(result);
    }

    // Close connection
    mysql_close(conn);
    return 0;
}