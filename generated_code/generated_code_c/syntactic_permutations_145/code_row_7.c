// Include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

// Define variables
char stock_name[50];
int quantity;

// Function to buy stock
void buy_stock(MYSQL *conn) {
    // Create query statement
    char query[200] = "INSERT INTO stocks (stock_name, quantity) VALUES ('";
    strcat(query, stock_name);
    strcat(query, "', ");
    sprintf(query + strlen(query), "%d", quantity);
    strcat(query, ")");
    
    // Execute query statement
    if (mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
    }
}

// Function to buy stock
void buy_function(MYSQL *conn) {
    // Create query statement
    char query[200] = "SELECT quantity FROM stocks WHERE stock_name = '";
    strcat(query, stock_name);
    strcat(query, "'");
    
    // Execute query statement
    if (mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
    }
}

// Main function
int main() {
    // Create database connection
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    // Connect to database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "stocks", 0, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
    }
    
    // Call buy stock function
    buy_stock(conn);
    
    // Call buy function
    buy_function(conn);
    
    // Close database connection
    mysql_close(conn);
    
    return 0;
}