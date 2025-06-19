#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "main.h"
#define SERVER_IP "localhost"
#define DATABASE "webapp"
#define USERNAME "admin"
#define PASSWORD "password"

int isModerator(char *username) {
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[50];
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, SERVER_IP, USERNAME, PASSWORD, DATABASE, 3306, NULL, 0)) {
    printf("Error connecting to database\n");
    return -1;
  }
  sprintf(query, "SELECT role FROM users WHERE username = '%s'", username);
  if (mysql_query(conn, query)) {
    printf("Error running query\n");
    mysql_close(conn);
    return -1;
  }
  res = mysql_store_result(conn);
  row = mysql_fetch_row(res);
  mysql_free_result(res);
  mysql_close(conn);
  if (strcmp(row[0], "moderator") == 0) {
    return 1;
  }
  return 0;
}

int main() {
  app.get("/isModerator", [](const httplib::Request &req, httplib::Response &res) {
    char *username = req.query("username");
    if (isModerator(username)) {
      res.set_content("true", "text/plain");
    } else {
      res.set_content("false", "text/plain");
    }
  });
}