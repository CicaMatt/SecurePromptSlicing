c


// Import required libraries

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

// Define the main function
int main() {

  // Create a database connection handle and initialize it to NULL
  MYSQL* conn = NULL;

  // Allocate memory for the database connection handle
  conn = mysql_init(NULL);

  // Connect to the database with the given credentials
  if (!mysql_real_connect(conn, "localhost", "root", "password", "mydb", 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  // Define the SQL query to insert a new user into the database
  char sql[256];
  sprintf(sql, "INSERT INTO users (username, password) VALUES ('%s', '%s');", "john", "doe");

  // Execute the SQL query
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  // Print a success message
  printf("User registered successfully!\n");

  // Free memory and close the database connection
  mysql_free_result(mysql_store_result(conn));
  mysql_close(conn);
  return 0;
}