#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    void insert_user_message_in_db(char *username, char *message) {
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row;
      char *server = "localhost";
      char *user = "root";
      char *password = "password";
      char *database = "messages";
      conn = mysql_init(NULL);
    
      if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      char query[256];
      sprintf(query, "INSERT INTO messages (username, message) VALUES ('%s', '%s')", username, message);
      if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      mysql_close(conn);
    }
    
    void post() {
      char *username = getenv("USERNAME");
      char *message = getenv("MESSAGE");
      insert_user_message_in_db(username, message);
      header("Location: /index.html", TRUE, 302);
    }
    
    int main() {
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row;
      char *server = "localhost";
      char *user = "root";
      char *password = "password";
      char *database = "messages";
      conn = mysql_init(NULL);
    
      if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      char query[256];
      sprintf(query, "SELECT * FROM messages");
      if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      res = mysql_store_result(conn);
      int num_rows = mysql_num_rows(res);
    
      printf("<!DOCTYPE html>\n");
      printf("<html>\n");
      printf("  <head>\n");
      printf("    <title>Messages</title>\n");
      printf("  </head>\n");
      printf("  <body>\n");
      printf("    <h1>Messages</h1>\n");
      printf("    <ul>\n");
    
      for (int i = 0; i < num_rows; i++) {
        row = mysql_fetch_row(res);
        char *username = row[0];
        char *message = row[1];
        time_t timestamp = atoi(row[2]);
    
        printf("      <li>\n");
        printf("        <strong>%s</strong>: %s\n", username, message);
        printf("        <small>(posted on %s)</small>\n", ctime(&timestamp));
        printf("      </li>\n");
      }
    
      printf("    </ul>\n");
      printf("  </body>\n");
      printf("</html>\n");
    
      mysql_free_result(res);
      mysql_close(conn);
      return 0;
    }