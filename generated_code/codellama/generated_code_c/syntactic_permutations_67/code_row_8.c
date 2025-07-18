#include <stdio.h>
    #include <mysql/mysql.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(int argc, char **argv) {
      if (argc != 2) {
        printf("Usage: %s image_file\n", argv[0]);
        return 1;
      }
      const char *image_file = argv[1];
    
      // MySQL connection settings
      char *server = "localhost";
      char *user = "root";
      char *password = "";
      char *database = "images";
      int port = 3306;
      
      // Create a MySQL connection handle
      MYSQL *conn = mysql_init(NULL);
    
      // Connect to the MySQL server
      if (!mysql_real_connect(conn, server, user, password, database, port, NULL, 0)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return 1;
      }
    
      // SQL query to insert an image file into the images table
      char sql[256];
      sprintf(sql, "INSERT INTO images (image) VALUES ('%s')", image_file);
      
      // Execute the SQL query
      if (mysql_query(conn, sql)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return 1;
      }
    
      // Close the MySQL connection handle
      mysql_close(conn);
      
      return 0;
    }