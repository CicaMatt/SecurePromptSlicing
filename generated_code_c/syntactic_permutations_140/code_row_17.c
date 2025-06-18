#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    int main() { 
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row;
      char *server = "localhost";
      char *user = "root";
      char *password = "root"; /* set me first */
      char *database = "mysql";
      conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
       }
      if (mysql_query(conn, "select username from users")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
      res = mysql_store_result(conn);
      while ((row = mysql_fetch_row(res)) != NULL) {
       if (strcmp(username, row[0])) {
         printf("%s\n", row[0]);
         return 0;
        }
      }
      return -1;
    }