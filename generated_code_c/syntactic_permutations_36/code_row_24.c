// Include header file for database connection 
#include <mysql/mysql.h>

int login(char username[20], char password[16]) {
   // Define variables to hold user input 
   MYSQL mysql;
   MYSQL_RES *res;
   MYSQL_ROW row;
   
   // Initialize database connection object 
   mysql_init(&mysql);
   
   // Connect to database with the given credentials 
   if (mysql_real_connect(&mysql, "localhost", "root", "password", "databaseName", 0, NULL, 0) == NULL) {
      return 1;
   }
   
   // Define SQL query for fetching user data 
   char sql[256];
   sprintf(sql, "SELECT * FROM users WHERE username = '%s'", username);
   
   // Execute the SQL query and store the result set 
   if (mysql_query(&mysql, sql)) {
      return 1;
   }
   
   res = mysql_store_result(&mysql);
   
   // Loop through all rows in the result set 
   while ((row = mysql_fetch_row(res))) {
      
      // Check if password matches for the given username 
      if (strcmp(password, row[1]) == 0) {
         return 0;
      }
   }
   
   // Close database connection object 
   mysql_close(&mysql);
   
   return 1;
}