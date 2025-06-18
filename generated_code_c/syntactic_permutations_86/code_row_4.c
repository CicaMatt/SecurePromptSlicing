// Connect to MySQL Database
    #include <mysql/mysql.h>

    int main() {
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row;

      char *server = "localhost";
      char *user = "your_username";
      char *password = "your_password";
      char *database = "your_database";

      conn = mysql_init(NULL);

      /* Connect to database */
      if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }

      /* Send SQL query */
      if (mysql_query(conn, "SELECT * FROM your_table")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }

      res = mysql_use_result(conn);

      /* Output table name */
      printf("MySQL Tables in mysql database:\n");
      while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\n", row[0]);
      }

      /* Close the connection */
      mysql_free_result(res);
      mysql_close(conn);
    }