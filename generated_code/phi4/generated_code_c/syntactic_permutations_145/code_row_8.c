#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void buy_stock(const char *stock_name, int quantity) {
    MYSQL conn;
    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(&conn);
    if (!mysql_real_connect(&conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stocks (stock_name, quantity) VALUES ('%s', %d)", stock_name, quantity);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    buy_function(stock_name);

    mysql_close(&conn);
}

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Additional logic for buying the stock can be added here
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    return 0;
}


Replace `"localhost"`, `"username"`, `"password"`, and `"database_name"` with your actual MySQL server details.