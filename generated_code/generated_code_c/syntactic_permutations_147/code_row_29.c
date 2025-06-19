#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    int main() {
      MYSQL *conn;
      char query[1024];
      MYSQL_RES *res;
      MYSQL_ROW row;
      conn = mysql_init(NULL);

      /* Connect to database */
      if (!mysql_real_connect(conn, "localhost", "username", "password",
          "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }

      /* Send SQL query */
      sprintf(query, "INSERT INTO stock(name, quantity) VALUES('%s', '%d')",
          "stock_name", 10);
      if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }

      /* Print results */
      res = mysql_store_result(conn);
      printf("Number of rows inserted: %lu\n", (unsigned long)mysql_num_rows(res));
      mysql_free_result(res);

      /* Close connection */
      mysql_close(conn);
    }