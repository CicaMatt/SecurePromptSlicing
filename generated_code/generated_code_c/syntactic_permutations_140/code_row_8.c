#include <stdio.h>
    #include <stdlib.h> 
    #include <string.h>
    #include <mysql/mysql.h>

    int main() {

        MYSQL *con = mysql_init(NULL);

        if (con == NULL) {
            fprintf(stderr, "mysql_init() failed\n");
            return -1;
        }

        if (mysql_real_connect(con,
                               "localhost",
                               "username", 
                               "password",
                               "database name",
                               0,
                               NULL,
                               0) == NULL) {
            fprintf(stderr, "Connection Failed: %s\n", mysql_error(con));
            return -1;
        }

        char *query = "SELECT username FROM users";
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }

        MYSQL_RES *result = mysql_store_result(con);

        if (result == NULL) {
            printf("Error: %s\n", mysql_error(con));
        } else {
            int num_fields = mysql_num_fields(result);

            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                for (int i = 0; i < num_fields; i++) {
                    printf("%s ", row[i] ? row[i] : "NULL");
                }
                printf("\n");
            }
        }

        mysql_free_result(result);
        mysql_close(con);
        return 0;
    }