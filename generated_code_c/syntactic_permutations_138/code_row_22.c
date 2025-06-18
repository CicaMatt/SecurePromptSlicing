#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Define the function that will be called when the route is called
int main() {
    // Connect to the database
    MYSQL mysql;
    if (mysql_init(&mysql)) {
        printf("MySQL initialised successfully.\n");
    } else {
        printf("Failed to initialise MySQL.\n");
        return 1;
    }

    // Define a query to check the database is connected properly
    const char* query = "SELECT version();";

    // Execute the query and store the result in the 'result' variable
    MYSQL_RES* result = mysql_store_result(&mysql);

    // Fetch the first row of the result
    MYSQL_ROW row = mysql_fetch_row(result);

    // Print the result
    printf("MySQL version: %s\n", row[0]);

    return 0;
}