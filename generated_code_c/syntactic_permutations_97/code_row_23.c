/* 
 * File:   main.c
 * Author: user123456789
 *
 * Created on 17 March 2022, 12:53 AM
 */


 #include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "database_name"
int main() {
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char *query = "SELECT username FROM table WHERE username='username'";
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
    printf("Error connecting to database! %s", mysql_error(conn));
    return 1;
  }
  if (mysql_query(conn, query)) {
    printf("Error making query: %s", mysql_error(conn));
    return 1;
  }
  res = mysql_store_result(conn);
  int num_rows = mysql_num_rows(res);
  if (num_rows == 1) {
    printf("User already exists.\n");
  } else {
    char *insert_query = "INSERT INTO table (username, password, first_name, last_name, email) VALUES ('username', 'password', 'first_name', 'last_name', 'email')";
    if (mysql_query(conn, insert_query)) {
      printf("Error making query: %s", mysql_error(conn));
      return 1;
    }
    printf("Registration successful.\n");
  }
  return (EXIT_SUCCESS);
}