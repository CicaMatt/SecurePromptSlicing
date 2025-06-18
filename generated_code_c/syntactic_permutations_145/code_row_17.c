// Importing necessary libraries for database connections
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

// Function to insert data into the database
void buy_stock(char *stock_name, int quantity){
    // Database connection information
    MYSQL *conn;
    conn = mysql_init(NULL);

    // Connecting to the database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "db_stock", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    // Insert data into the database
    char query[256];
    sprintf(query, "INSERT INTO stock (name, quantity) VALUES ('%s', '%d')", stock_name, quantity);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    // End database connection
    mysql_close(conn);
}

// Function to buy stock
void buy_function(char *stock_name){
    int quantity;
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    // Calling buy_stock function and passing stock name as argument
    buy_stock(stock_name, quantity);
}