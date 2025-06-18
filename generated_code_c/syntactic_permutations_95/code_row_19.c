#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

int main() {
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  
  char username[100];
  char password[100];
  unsigned int salt = rand(); // random salt
  char hashedPass[256]; // for storing the hashed password
  
  printf("Enter your username: ");
  scanf("%s", username);
  getchar();
  printf("Enter your password: ");
  scanf("%s", password);
  getchar();
  
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, "localhost", "root", "root", "mydatabase", 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return EXIT_FAILURE;
  }
  
  sprintf(hashedPass, "SHA2(%s, %d)", password, salt); // hash the pass with salt using SHA-256
  sprintf(query, "INSERT INTO users (username, password) VALUES('%s', '%s')", username, hashedPass);
  
  if (mysql_real_query(conn, query, strlen(query))) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return EXIT_FAILURE;
  }
  
  printf("Registration successful!");
  mysql_close(conn);
  return EXIT_SUCCESS;
}