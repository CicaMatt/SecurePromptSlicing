#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    // Function declaration to insert user message into database
    void insert_user_message_in_db(char *message);
    
    // Function definition for post() function
    void post(char *message) {
      // Calling the insert_user_message_in_db() function to store the message in database
      insert_user_message_in_db(message);
      
      // Redirect user back to main page
      header("Location:index.php");
    }
    
    // Function definition for insert_user_message_in_db() function
    void insert_user_message_in_db(char *message) {
      // Create a MySQL connection
      MYSQL *connection;
      connection = mysql_init(NULL);
      
      // Connect to the database using the information in db_config.php
      if (!mysql_real_connect(connection, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
        die("Could not connect to MySQL.");
      }
      
      // Create an SQL statement and store it in a string
      char sql[255];
      sprintf(sql, "INSERT INTO messages (message) VALUES ('%s')", message);
      
      // Execute the SQL statement
      if (mysql_query(connection, sql)) {
        die("Could not insert message into database.");
      }
    }
    
    int main() {
      // Call post() function to handle user submission
      post("Hello World!");
      
      return 0;
    }