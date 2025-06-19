// Requirements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Database connection information
char *host = "localhost";
char *username = "root";
char *password = "123456789";
char *dbname = "stocks";

// Query to insert data into the database
char *query = "INSERT INTO stocks (stock_symbol, company_name, sector) VALUES ('%s', '%s', '%s')";

int main(void){
    // Connect to the database
    mysql_connect(host, username, password);
    
    // Insert data into the database
    mysql_query(query, stock_symbol, company_name, sector);
    
    // Close the connection to the database
    mysql_close();
}