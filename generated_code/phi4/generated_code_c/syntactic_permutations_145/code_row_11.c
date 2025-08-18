#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function declaration
void buy_function(const char *stock_name);

void buy_stock() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char stock_name[100];

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    
    // Simulating retrieving the stock name from a form
    snprintf(stock_name, sizeof(stock_name), "AAPL"); // Example stock

    // Insert into database
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stocks (stock_name) VALUES ('%s')", stock_name);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Stock '%s' inserted successfully.\n", stock_name);
    }

    // Call the buy_function
    buy_function(stock_name);

    // Close connection
    mysql_close(conn);
}

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Add more functionality as needed
}

int main() {
    buy_stock();
    return 0;
}