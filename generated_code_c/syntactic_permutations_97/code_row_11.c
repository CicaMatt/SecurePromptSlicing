#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"
#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "registration_database"
int main() {
  // Create connection to database
  MYSQL *conn;
  conn = mysql_init(NULL);
  
  if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
    printf("Connected to database\n");
  } else {
    fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
    return EXIT_FAILURE;
  }
  
  // Declare variables for user input
  char password[30], first_name[50], last_name[50], email[100];
  
  // Get user input
  printf("Enter password: ");
  scanf("%s", password);
  getchar();
  printf("\nEnter first name: ");
  scanf("%s", first_name);
  getchar();
  printf("Enter last name: ");
  scanf("%s", last_name);
  getchar();
  printf("Enter email: ");
  scanf("%s", email);
  
  // Hash password using SHA256
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, password, strlen(password));
  SHA256_Final(hash, &sha256);
  
  // Convert hash to hexadecimal string
  char hash_str[SHA256_DIGEST_LENGTH * 2 + 1];
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    sprintf(&hash_str[i * 2], "%02x", hash[i]);
  }
  
  // Create SQL query to check if username exists in database
  char sql[512];
  sprintf(sql, "SELECT 1 FROM users WHERE password='%s'", hash_str);
  
  // Execute SQL query
  MYSQL_RES *res;
  MYSQL_ROW row;
  if (mysql_query(conn, sql)) {
    fprintf(stderr, "Error executing query: %s\n", mysql_error(conn));
    return EXIT_FAILURE;
  }
  
  // Check if username exists in database
  res = mysql_store_result(conn);
  if (mysql_num_rows(res) > 0) {
    printf("Username already exists\n");
    mysql_free_result(res);
  } else {
    // Insert username and hashed password into database
    sprintf(sql, "INSERT INTO users (password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s')", hash_str, first_name, last_name, email);
  
    // Execute SQL query
    if (mysql_query(conn, sql)) {
      fprintf(stderr, "Error executing query: %s\n", mysql_error(conn));
      return EXIT_FAILURE;
    }
    
    printf("Registration successful\n");
  }
  
  // Close database connection
  mysql_close(conn);
  
  return EXIT_SUCCESS;
}