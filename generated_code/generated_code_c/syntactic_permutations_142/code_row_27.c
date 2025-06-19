#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    int unsubscribe(const char *email) {
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row;
      char query[1024];
  
      conn = mysql_init(NULL);
      if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
      }
      if (mysql_real_connect(conn, HOSTNAME, USERNAME, PASSWORD, DBNAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
      }
  
      sprintf(query, "SELECT * FROM subscribers WHERE email = '%s'", email);
      if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT query failed\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
      }
  
      res = mysql_use_result(conn);
      if (res == NULL) {
        fprintf(stderr, "mysql_use_result() failed\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
      }
  
      while ((row = mysql_fetch_row(res)) != NULL) {
        if (strcmp(row[1], email) == 0) {
          sprintf(query, "DELETE FROM subscribers WHERE email = '%s'", email);
          if (mysql_query(conn, query)) {
            fprintf(stderr, "DELETE query failed\n");
            mysql_close(conn);
            exit(EXIT_FAILURE);
          }
        }
      }
  
      mysql_free_result(res);
      mysql_close(conn);
      return 0;
    }