// Include necessary headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

// Function for connecting to the MySQL database 
void db_connect(MYSQL** conn)
{
    *conn = mysql_init(NULL);
    
    // Connection information and parameters
    if (!mysql_real_connect(*conn, "localhost", "root", "", "stock_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(*conn));
        exit(1);
    }
}

// Function for inserting a new stock into the database
void insert_stock(MYSQL* conn, char* stock_name, int quantity)
{
    // SQL query to insert the new stock
    char sql[256];
    sprintf(sql, "INSERT INTO stocks (name, quantity) VALUES ('%s', %d)", stock_name, quantity);
    
    // Execute the SQL query
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
}

// Function for displaying the current stock inventory
void display_stocks(MYSQL* conn)
{
    // SQL query to select all rows from the "stocks" table
    char sql[256];
    sprintf(sql, "SELECT * FROM stocks");
    
    // Execute the SQL query
    MYSQL_RES* res = mysql_query(conn, sql);
    if (res) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    
    // Print each row in the result set
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        printf("%s (%d)\n", row[1], atoi(row[2]));
    }
}

// Main entry point into the program
int main()
{
    // Connect to the database
    MYSQL* conn;
    db_connect(&conn);
    
    // Insert a new stock into the database
    char* stock_name = "Google";
    int quantity = 100;
    insert_stock(conn, stock_name, quantity);
    
    // Display the current stock inventory
    display_stocks(conn);
    
    // Close the database connection
    mysql_close(conn);
}