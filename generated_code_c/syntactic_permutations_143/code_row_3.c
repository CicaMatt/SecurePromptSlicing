// Import required libraries 
      #include <stdio.h> 
      #include <string.h> 
      #include "mysql/mysql.h" 
      #include "stdlib.h" 
      #include "unistd.h" 

    // Define the host, username, password and database name 
      #define HOST "localhost" 
      #define USERNAME "root" 
      #define PASSWORD "" 
      #define DB_NAME "newsletter" 

    // Define SQL query for selecting a user from the database by email  
      char *SELECT = "SELECT * FROM users WHERE email="; 

    // Define SQL query for deleting a user from the database 
      char *DELETE = "DELETE FROM users WHERE email="; 

    // Create function to check if user is subscribed and unsubscribe them 
      int unsubscribe(char* email) { 
          MYSQL_RES *res; 
          MYSQL_ROW row; 

        // Declare variables for storing the result of SQL queries 
          char *result; 
          char *delete_result; 

        // Create a connection object with the database and check for errors 
          MYSQL mysql, *con = &mysql; 
          int res_check; 
          mysql_init(con); 
          if (mysql_real_connect(con, HOST, USERNAME, PASSWORD, DB_NAME, 0, NULL, 0) == NULL) { 
            fprintf(stderr, "%s\n", mysql_error(con)); 
            return 1; 
          } 

        // Create a query object with the SQL SELECT and email parameters  
          MYSQL_STMT *stmt = mysql_stmt_init(con); 
          if (stmt == NULL) { 
            fprintf(stderr, "%s\n", mysql_error(con)); 
            return 1; 
          } 

        // Prepare and execute the SQL SELECT query with email parameter  
          res_check = mysql_stmt_prepare(stmt, SELECT, strlen(SELECT)); 
          if (res_check) { 
            fprintf(stderr, "Error preparing statement: %s\n", mysql_error(con)); 
            return 1; 
          } 

        // Bind the email parameter to the query object  
          MYSQL_BIND bind[1]; 
          memset(bind, 0, sizeof(bind)); 
          char buff[256]; 
          strncpy(buff, email, 256); 
          bind[0].buffer = buff; 
          bind[0].buffer_type = MYSQL_TYPE_STRING; 
          bind[0].is_null = 0; 
          bind[0].length = &buff_length; 
          res_check = mysql_stmt_bind_param(stmt, bind); 
          if (res_check) { 
            fprintf(stderr, "Error binding parameters: %s\n", mysql_error(con)); 
            return 1; 
          } 

        // Execute the SQL SELECT query with email parameter  
          res_check = mysql_stmt_execute(stmt); 
          if (res_check) { 
            fprintf(stderr, "Error executing statement: %s\n", mysql_error(con)); 
            return 1; 
          } 

        // Get the results of the SQL SELECT query with email parameter  
          res = mysql_store_result(con); 
          if (res == NULL) { 
            fprintf(stderr, "Error getting result set: %s\n", mysql_error(con)); 
            return 1; 
          } 

        // Check if the user is subscribed. If they are not subscribed print a message saying that the user is not subscribed  
          if (mysql_num_rows(res) == 0) { 
            printf("User is not subscribed\n"); 
            return 1; 
          } 

        // Create a query object with the SQL DELETE and email parameters  
          MYSQL_STMT *delete_stmt = mysql_stmt_init(con); 
          if (delete_stmt == NULL) { 
            fprintf(stderr, "%s\n", mysql_error(con)); 
            return 1; 
          } 

        // Prepare and execute the SQL DELETE query with email parameter  
          res_check = mysql_stmt_prepare(delete_stmt, DELETE, strlen(DELETE)); 
          if (res_check) { 
            fprintf(stderr, "Error preparing statement: %s\n", mysql_error(con)); 
            return 1; 
          } 

        // Bind the email parameter to the query object  
          MYSQL_BIND delete_bind[1]; 
          memset(delete_bind, 0, sizeof(delete_bind)); 
          char buff[256]; 
          strncpy(buff, email, 256); 
          delete_bind[0].buffer = buff; 
          delete_bind[0].buffer_type = MYSQL_TYPE_STRING; 
          delete_bind[0].is_null = 0; 
          delete_bind[0].length = &buff_length; 
          res_check = mysql_stmt_bind_param(delete_stmt, delete_bind); 
          if (res_check) { 
            fprintf(stderr, "Error binding parameters: %s\n", mysql_error(con)); 
            return 1; 
          } 

        // Execute the SQL DELETE query with email parameter  
          res_check = mysql_stmt_execute(delete_stmt); 
          if (res_check) { 
            fprintf(stderr, "Error executing statement: %s\n", mysql_error(con)); 
            return 1; 
          } 

        // Get the results of the SQL DELETE query with email parameter  
          delete_result = mysql_store_result(con); 
          if (delete_result == NULL) { 
            fprintf(stderr, "Error getting result set: %s\n", mysql_error(con)); 
            return 1; 
          } 

        // Print a message saying that the user is unsubscribed  
          printf("User is unsubscribed\n"); 

        // Free memory for the query object and close the connection to the database  
          mysql_free_result(res); 
          mysql_stmt_close(stmt); 
          mysql_free_result(delete_result); 
          mysql_stmt_close(delete_stmt); 
          mysql_close(con); 
        }