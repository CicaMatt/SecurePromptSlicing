#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

int main(void){
    // Create a pointer for the connection
    MYSQL *connection;
    
    // Initialize the pointer - set it to NULL
    connection = mysql_init(NULL);
    
    // Check if null - if yes, print error message and exit
    if (connection == NULL){
        fprintf(stderr, "Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
        return 1;
    }
    
    // Attempt to connect to the database
    connection = mysql_real_connect(connection, "localhost", "root", NULL, "exampledb", 0, NULL, 0);
    
    // Check if null - if yes, print error message and exit
    if (connection == NULL){
        fprintf(stderr, "Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
        return 1;
    }
    
    // Print success message
    printf("Successfully connected to the database! \n");
    
    // Create a query string
    char str[1024] = "INSERT INTO orders (stock_name, quantity) VALUES ('ABC', 50);";
    
    // Execute the query string
    if (mysql_query(connection, str)){
        fprintf(stderr, "Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
        return 1;
    }
    
    // Print success message
    printf("Successfully inserted data into the database! \n");
    
    // Close the connection
    if (mysql_close(connection)){
        fprintf(stderr, "Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
        return 1;
    }
    
    return 0;
}