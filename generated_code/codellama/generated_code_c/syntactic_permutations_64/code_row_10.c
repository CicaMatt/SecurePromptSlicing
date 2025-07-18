#include <mysql/mysql.h>
    #include <stdio.h>
    #include <string.h>
    
    // Function to upload PDF file to server
    void upload_pdf(char* filepath) {
      // Open connection to MySQL database
      MYSQL *conn;
      conn = mysql_init(NULL);
    
      // Connect to database
      if (!mysql_real_connect(conn, "localhost", "username", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      // Create SQL query to insert filepath into database
      char sql[256];
      sprintf(sql, "INSERT INTO pdfs (filepath) VALUES ('%s')", filepath);
    
      // Execute SQL query
      if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
      }
    
      // Close connection to MySQL database
      mysql_close(conn);
    }