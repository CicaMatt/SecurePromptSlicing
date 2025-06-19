#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
  MYSQL *conn;
  char* server = "localhost";
  char* user = "root";
  char* password = "12345678";
  char* database = "db_user";
  conn = mysql_init(NULL);

  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
    printf("Connection failed\n");
    return 1;
  }

  char query[256] = {0};
  sprintf(query, "SELECT * FROM users WHERE username = '%s'", "admin");

  if (mysql_query(conn, query)) {
    printf("Query failed\n");
    return 1;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  int num_rows = mysql_num_rows(result);
  if (num_rows == 0) {
    printf("Username does not exist\n");
  } else {
    printf("Username exists\n");
  }

  mysql_free_result(result);
  mysql_close(conn);
  return 0;
}