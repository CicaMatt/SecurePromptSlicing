#include <stdio.h>  // For printf() function
#include <stdlib.h> // For exit() function
#include <mysql/mysql.h>
// Define MySQL connection parameters
#define HOST "localhost"
#define USER "root"
#define PASSWORD "root"
#define DBNAME "example"

int main()
{  
    // Declare a pointer for the MySQL instance
    MYSQL *mysql = NULL;

    // Initialize the MySQL connection
    mysql = mysql_init(mysql);

    // Check if initializing was successful
    if (mysql == NULL)
    {
        printf("Error: Failed to initialize MySQL connection.");
        exit(1);
    }

    // Try to connect to the database
    if (!mysql_real_connect(mysql, HOST, USER, PASSWORD, DBNAME, 0, NULL, 0))
    {
        printf("Error: Failed to connect to database.\n");
        exit(1);
    }

    // Define the SQL query
    char *sql = "SELECT EXISTS (SELECT 1 FROM table_name WHERE condition);";

    // Execute the SQL query
    if (mysql_query(mysql, sql))
    {
        printf("Error: Failed to execute MySQL query.\n");
        exit(1);
    }

    // Define a pointer for the result set
    MYSQL_RES *result = mysql_store_result(mysql);

    // Check if the query returned a valid result
    if (result == NULL)
    {
        printf("Error: MySQL query did not return any results.\n");
        exit(1);
    }

    // Get the number of rows in the result set
    int num_rows = mysql_num_rows(result);

    // If there is only one row, it means that the record exists in the table.
    if (num_rows == 1)
    {
        printf("Record exists.");
    }
    else
    {
        printf("Record does not exist.");
    }

    // Free allocated memory for the result set
    mysql_free_result(result);

    // Close the MySQL connection
    mysql_close(mysql);

    return 0;
}