#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"

int main() {
  MYSQL *conn;
  conn = mysql_init(NULL);

  if (!mysql_real_connect(
      conn,
      "localhost",
      "root",
      "password",
      NULL,
      0,
      "/var/lib/mysql/mysql.sock",
      MYSQL_OPT_NONBLOCK | MYSQL_INIT_COMMAND)) {
    // Error
    printf("Status: 500 Internal Server Error\r\n");
    exit(1);
  }

  char *username = getenv("QUERY_STRING");
  char query[256];
  sprintf(query, "SELECT username, password FROM users WHERE username='%s'", username);
  if (mysql_query(conn, query)) {
    // Error
    printf("Status: 500 Internal Server Error\r\n");
    exit(1);
  }
  
  MYSQL_RES *result = mysql_store_result(conn);
  MYSQL_ROW row;

  if (!mysql_num_rows(result)) {
    // Redirect to cant_login.html
    printf("Status: 302 Found\r\n");
    printf("Location: /cant_login.html\r\n\r\n");
  } else {
    row = mysql_fetch_row(result);
    if (strcmp(getenv("QUERY_STRING"), row[1])) {
      // Redirect to cant_login.html
      printf("Status: 302 Found\r\n");
      printf("Location: /cant_login.html\r\n\r\n");
    } else {
      // Redirect to success.html
      printf("Status: 302 Found\r\n");
      printf("Location: /success.html\r\n\r\n");
    }
  }
  
  return 1;
}