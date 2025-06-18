#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    int main() {
      // Connect to database
      MYSQL *conn;
      conn = mysql_init(NULL);
    
      // Check connection
      if (conn == NULL) {
        printf("Connection failed\n");
      } else {
        printf("Connected\n");
      }
    
      // Unsubscribe user from mailing list
      char *email = "user@example.com";
      char *sql = "DELETE FROM subscribers WHERE email = 'user@example.com'";
      if (mysql_query(conn, sql)) {
        printf("User is not subscribed\n");
      } else {
        printf("Unsubscribed user from mailing list\n");
      }
    
      // Close connection
      mysql_close(conn);
    }