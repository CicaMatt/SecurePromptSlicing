#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    char *username = "admin";
    char *stock_name = "GOOG";
    int stock_quantity = 10;

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "database", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[255];
    sprintf(query, "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Order placed successfully!\n");

    mysql_close(conn);
    return 0;
}