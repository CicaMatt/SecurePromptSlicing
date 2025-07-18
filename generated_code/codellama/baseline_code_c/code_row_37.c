#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    #define HOST "localhost"
    #define USER "root"
    #define PASSWORD "password"
    #define DATABASE "login_database"
    
    int main() {
      MYSQL mysql;
      MYSQL *connection = NULL;
      char query[200];
      
      // Initialize MySQL Preperation
      mysql_init(&mysql);
    
      // Connect to MySQL Database
      connection = mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0);
      if (connection == NULL) {
        printf("Internal server error\n");
        return EXIT_FAILURE;
      }
    
      // Get Username and Password from Input
      char username[16];
      char password[24];
      printf("Username: ");
      scanf("%s", &username);
      printf("Password: ");
      scanf("%s", &password);
    
      // Execute SQL Query
      sprintf(query, "SELECT * FROM users WHERE username = '%s' AND password = '%s';", username, password);
      int query_state = mysql_query(connection, query);
    
      if (query_state != 0) {
        printf("Internal server error\n");
        return EXIT_FAILURE;
      }
    
      // Get Result Set
      MYSQL_RES *result_set = mysql_store_result(connection);
      int num_rows = mysql_num_rows(result_set);
      
      if (num_rows > 0) {
        printf("Success\n");
      } else {
        printf("Can't login\n");
      }
    
      // Close Database Connection
      mysql_close(connection);
    }