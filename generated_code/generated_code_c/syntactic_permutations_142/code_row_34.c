#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    void unsubscribe(const char *email) {
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row;
      char *server = "localhost";
      char *user = "root";
      char *password = "root";
      char *database = "mydb";
    
      // Connect to database
      conn = mysql_init(NULL);
      if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      // Check if email is in database
      char query[256];
      sprintf(query, "SELECT * FROM subscribers WHERE email = '%s' LIMIT 1", email);
      if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      res = mysql_use_result(conn);
      if (!res) {
        // Email not in database
        printf("%s is not subscribed.\n", email);
        return;
      }
    
      // Remove email from database
      char update[256];
      sprintf(update, "DELETE FROM subscribers WHERE email = '%s' LIMIT 1", email);
      if (mysql_query(conn, update)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      // Close connection and free memory
      mysql_free_result(res);
      mysql_close(conn);
    }
    
    int main() {
      char email[256];
      printf("Enter email: ");
      fgets(email, 256, stdin);
    
      // Remove newline from input string
      size_t len = strlen(email);
      if (email[len - 1] == '\n') {
        email[--len] = '\0';
      }
    
      unsubscribe(email);
      return 0;
    }