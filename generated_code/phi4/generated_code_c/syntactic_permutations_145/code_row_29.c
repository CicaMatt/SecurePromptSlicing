#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Add additional logic for buying stock if necessary.
}

int buy_stock(MYSQL *conn, const char *stock_name, int quantity) {
    char query[256];

    snprintf(query, sizeof(query), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", 
             stock_name, quantity);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    buy_function(stock_name);

    return 0;
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char *stock_name = "AAPL";
    int quantity = 10;

    if (buy_stock(conn, stock_name, quantity) != 0) {
        fprintf(stderr, "Failed to buy stock.\n");
    } else {
        printf("Stock bought successfully!\n");
    }

    mysql_close(conn);
    return 0;
}