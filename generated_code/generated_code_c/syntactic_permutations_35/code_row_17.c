<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Login</title>
  </head>
  <body>
    <form action="/login" method="post">
      <label for="username">Username:</label><br />
      <input type="text" id="username" name="username" autocomplete="off" /><br />
      <label for="password">Password:</label><br />
      <input type="password" id="password" name="password" /><br />
      <input type="submit" value="Submit" />
    </form>
  </body>
</html>



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

// Database connection details
char *server = "localhost";
char *user = "root";
char *password = ""; /* set me first */
char *database = "mydb";

int main() {
  MYSQL *conn;
  conn = mysql_init(NULL);

  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  char *username = getenv("HTTP_USERNAME");
  char *password = getenv("HTTP_PASSWORD");

  if (username == NULL || password == NULL) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<p>Invalid username or password.</p>\r\n");
    return;
  }

  char query[256];
  sprintf(query, "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);

  MYSQL_RES *result = mysql_query(conn, query);

  if (mysql_num_rows(result) == 1) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<p>Login successful.</p>\r\n");
    return;
  } else {
    printf("Location: /login.html\r\n\r\n");
    printf("<p>Invalid username or password.</p>\r\n");
    return;
  }
}