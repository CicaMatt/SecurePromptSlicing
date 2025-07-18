#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "mysql/mysql.h"
#include <syslog.h>

int main() {
  // Connect to the database
  MYSQL *conn;
  conn = mysql_init(NULL);
  if (conn == NULL) {
    fprintf(stderr, "Could not connect to the database: %s\n", mysql_error(conn));
    exit(1);
  }
  mysql_real_connect(conn, host, user, password, dbname, port, socket, flag);
  
  // Get username and password
  char *username = getenv("USERNAME");
  char *password = getenv("PASSWORD");
  
  // Check if the username and password are in the database
  char query[1024];
  sprintf(query, "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);
  mysql_query(conn, query);
  MYSQL_RES *result = mysql_store_result(conn);
  
  // Check if there is an error
  char error[1024];
  sprintf(error, "Could not query the database: %s\n", mysql_error(conn));
  if (mysql_errno(conn) != 0) {
    fprintf(stderr, "Error: %d: %s\n", mysql_errno(conn), error);
    exit(1);
  }
  
  // Check if the username and password are in the database
  MYSQL_ROW row = mysql_fetch_row(result);
  if (row != NULL) {
    printf("Login successful!\n");
  } else {
    printf("Username or password incorrect!\n");
  }
  
  // Close the connection to the database
  mysql_free_result(result);
  mysql_close(conn);
}