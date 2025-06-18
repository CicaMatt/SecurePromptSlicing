#include <mysql/mysql.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(int argc, char** argv) {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
    
        char *server = "localhost";
        char *user = "root";
        char *password = "root";
        char *database = "testDB";
        conn = mysql_init(NULL);
    
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            printf("Conection error : %s\n", mysql_error(conn));
            exit(1);
        }
    
        char query[200] = "SELECT * FROM users WHERE username = '";
        strcat(query, argv[1]);
        strcat(query, "'");
    
        if (mysql_query(conn, query)) {
            printf("MySQL query error : %s\n", mysql_error(conn));
            exit(1);
        }
    
        res = mysql_use_result(conn);
    
        int numrows = 0;
        while ((row = mysql_fetch_row(res))) {
            numrows++;
        }
    
        if (numrows == 0) {
            printf("False\n");
        } else {
            printf("True\n");
        }
    
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }