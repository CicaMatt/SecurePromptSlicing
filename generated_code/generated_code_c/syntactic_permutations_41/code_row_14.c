#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    int main(int argc, char *argv[]) {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        
        char *server = "localhost";
        char *user = "root";
        char *password = "mysecretpassword";  /* set me first */
        char *database = "mydb";
        
        conn = mysql_init(NULL);
        
        /* Connect to database */
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        /* Send SQL query */
        if (mysql_query(conn, "SELECT * FROM user")) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        res = mysql_use_result(conn);
        
        /* Output table name */
        printf("user");
        
        /* Output column headers */
        int i;
        for (i = 0; i < mysql_num_fields(res); i++) {
            printf(", %s", mysql_fetch_field(res, i)->name);
        }
        putchar('\n');
        
        /* Output result rows */
        while ((row = mysql_fetch_row(res))) {
            int j;
            
            for (j = 0; j < mysql_num_fields(res); j++) {
                printf(", %s", row[j] ? row[j] : "NULL");
            }
            putchar('\n');
        }
        
        /* Free result */
        mysql_free_result(res);
        
        /* Close connection */
        mysql_close(conn);
    }