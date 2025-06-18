#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
 
void buy_stock(quantity) {
    MYSQL *conn;
    conn = mysql_init(NULL);
 
    if (!mysql_real_connect(conn, "database-host", "user", "password", "database-name", 0, NULL, 0)) {
        printf("error");
    } else {
        char query[100];
        sprintf(query, "INSERT INTO `stock` (quantity) VALUES ('%d')", quantity);
        if (mysql_query(conn, query)) {
            printf("error");
        } else {
            buy_function(quantity);
        }
    }
    mysql_close(conn);
}
 
void buy_function(int quantity) {
    // function body
}