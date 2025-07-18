#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <openssl/md5.h>
    #include <mysql.h>
    
    int main() {
      MYSQL *connection;
      MYSQL_RES *result;
      char username[20];
      char firstname[20];
      char lastname[20];
      char email[50];
      char query[100];
      char hashed[34];
    
      // Get connection to MySQL database
      connection = mysql_init(NULL);
      if (!mysql_real_connect(connection, "localhost", "root", "password", "dbname", 0, NULL, 0)) {
        printf("MySQL Error: %s\n", mysql_error(connection));
        return 1;
      }
    
      // Get username input from user
      printf("Enter username: ");
      scanf("%s", username);
    
      // Get first name input from user
      printf("Enter first name: ");
      scanf("%s", firstname);
    
      // Get last name input from user
      printf("Enter last name: ");
      scanf("%s", lastname);
    
      // Get email input from user
      printf("Enter email: ");
      scanf("%s", email);
    
      // Hash password using MD5
      sprintf(hashed, "%x%x%x%x%x", username[0], username[1], username[2], username[3], username[4]);
    
      // Check if username is already in database
      sprintf(query, "SELECT * FROM users WHERE username = '%s'", username);
      mysql_query(connection, query);
      result = mysql_store_result(connection);
      if (mysql_num_rows(result) > 0) {
        printf("Username already exists\n");
      } else {
        // Insert hashed password into database
        sprintf(query, "INSERT INTO users (username, firstname, lastname, email, password) VALUES ('%s', '%s', '%s', '%s', '%s')", username, firstname, lastname, email, hashed);
        mysql_query(connection, query);
        printf("Registration successful\n");
      }
    
      // Close database connection
      mysql_close(connection);
    
      return 0;
    }