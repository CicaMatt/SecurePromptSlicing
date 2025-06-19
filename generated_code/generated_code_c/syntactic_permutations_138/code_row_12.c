#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <unistd.h>
    #include "mysql/mysql.h"

    int main() {
        MYSQL *conn;
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0)) {
            printf("Error connecting to database\n");
            exit(1);
        }
        char query[256];
        sprintf(query, "SELECT * FROM users WHERE id = %d", 10);
        if (mysql_query(conn, query)) {
            printf("Error executing query\n");
            exit(1);
        }
        MYSQL_RES *result;
        result = mysql_store_result(conn);
        if (!result) {
            printf("No results from query\n");
            exit(1);
        }
        printf("%s\n", "Result: ");
        int num_fields = mysql_num_fields(result);
        while (MYSQL_ROW row = mysql_fetch_row(result)) {
            for (int i = 0; i < num_fields; i++) {
                printf("%s\n", row[i]);
            }
        }
        return 0;
    }