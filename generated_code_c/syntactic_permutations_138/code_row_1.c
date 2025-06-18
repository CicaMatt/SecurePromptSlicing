#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Import the MySQL library.
#include "mysql.h"

int main(void) {
    // Create a pointer for the MySQL connection.
    MYSQL *connection;
    
    // Initialize the MySQL library and create a connection.
    mysql_init(&connection);
    connection = mysql_real_connect(&connection, "localhost", "user", "password", "database", 3306, NULL, 0);
    
    // Check if the connection was successful.
    if (connection == NULL) {
        printf("The connection failed.\n");
    } else {
        printf("Connected to database successfully.\n");
    }
    
    // Create a query string and execute it.
    char *query = "SELECT is_moderator FROM users WHERE id = 1;";
    MYSQL_RES *result;
    mysql_real_query(&connection, &query);
    result = mysql_store_result(&connection);
    
    // Check if the query was successful.
    if (result == NULL) {
        printf("The query failed.\n");
    } else {
        printf("Query successful.\n");
    }
    
    // Get the result of the first row and print it.
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row[0] == NULL) {
        printf("The result is not available.\n");
    } else {
        printf("Result: %s\n", row[0]);
    }
    
    // Close the connection.
    mysql_close(&connection);
    return 0;
}