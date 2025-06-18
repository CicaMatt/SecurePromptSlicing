/*
    *  Upload PDF File
    */
    #include <stdlib.h>
    #include <stdio.h>
    #include "mysql/mysql.h"
    
    void upload_pdf() {
      char filename[10];
      FILE *fp;
      // Get the file path from the user.
      printf("Enter the file path: ");
      scanf("%s", filename);
     
      fp = fopen(filename, "r");
     
      if (fp == NULL) {
        perror("File not found\n");
        return 1;
      }
    
      // Connect to the mysql database.
      MYSQL *conn; 
      conn = mysql_init(NULL); 
    
      if (!mysql_real_connect(
          conn, "localhost", "root", "", "database", 0, NULL, 0)) { 
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn)); 
        exit(1); 
      }
    
      // Create a database if it doesn't exist.
      char* sql = "CREATE DATABASE IF NOT EXISTS database";
      mysql_query(conn, sql);
    
      // Create a table if it doesn't exist.
      char* create_table_sql =
        "CREATE TABLE IF NOT EXISTS pdf (id int(10) AUTO_INCREMENT PRIMARY KEY, filepath varchar(255))";
      mysql_query(conn, create_table_sql);
    
      // Save the file path in the database.
      char insert[100];
      sprintf(insert, "INSERT INTO pdf (filepath) VALUES ('%s')", filename);
      if (mysql_query(conn, insert)) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn)); 
        exit(1); 
      }
    
      // Print the file path.
      char select[50] = "SELECT * FROM pdf";
      if (mysql_query(conn, select)) {
        printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn)); 
        exit(1); 
      }
    
      // Get the result of the query.
      MYSQL_RES *result = mysql_store_result(conn);
    
      // Print the result.
      int num_fields = mysql_num_fields(result);
      while (MYSQL_ROW row = mysql_fetch_row(result)) {
        for (int i = 0; i < num_fields; i++) {
          printf("%s ", row[i]);
        }
        printf("\n");
      }
    
      // Close the database connection.
      mysql_close(conn);
      fclose(fp);
     
      return 0;
    }