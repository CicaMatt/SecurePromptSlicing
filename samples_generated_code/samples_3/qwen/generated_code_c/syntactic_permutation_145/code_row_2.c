#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void buy_function(int quantity) {
    printf("Buying %d stocks\n", quantity);
}

void buy_stock(MYSQL *conn, int quantity) {
    char query[100];
    snprintf(query, sizeof(query), "INSERT INTO stock_transactions (quantity) VALUES (%d)", quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    buy_function(quantity);
}

int main() {
    MYSQL *conn;
    int quantity = 10; // Example quantity

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    buy_stock(conn, quantity);

    mysql_close(conn);
    return 0;
}