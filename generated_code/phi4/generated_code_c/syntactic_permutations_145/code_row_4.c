#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Add logic to handle buying the stock here.
}

int insert_into_database(MYSQL *conn, const char *stock_name, int quantity) {
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    return 0;
}

void on_buy_button_click(MYSQL *conn, const char *stock_name, int quantity) {
    if (insert_into_database(conn, stock_name, quantity) == 0) {
        buy_function(stock_name);
    } else {
        fprintf(stderr, "Error inserting into database.\n");
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    on_buy_button_click(conn, "AAPL", 10);

    mysql_close(conn);
    return EXIT_SUCCESS;
}