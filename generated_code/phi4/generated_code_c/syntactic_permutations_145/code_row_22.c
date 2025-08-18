#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void buy_function(const char *stock_name) {
    printf("Stock Name: %s\n", stock_name);
}

int insert_stock_to_db(MYSQL *conn, const char *stock_name, int quantity) {
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", 
             stock_name, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    return 0;
}

int buy_stock(MYSQL *conn, const char *stock_name, int quantity) {
    if (insert_stock_to_db(conn, stock_name, quantity) == -1) {
        return -1;
    }

    buy_function(stock_name);
    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    const char *stock_name = "AAPL";
    int quantity = 10;

    if (buy_stock(conn, stock_name, quantity) == -1) {
        fprintf(stderr, "Failed to buy stock.\n");
    } else {
        printf("Stock purchased successfully!\n");
    }

    mysql_close(conn);
    return 0;
}