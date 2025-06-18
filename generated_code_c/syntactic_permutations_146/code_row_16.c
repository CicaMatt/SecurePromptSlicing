// Includes
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sqlite3.h>
    
    // Macros
    #define SQLITE_DB "stocks.db"
    #define SQLITE_TABLE "stocks"
    #define USERNAME "user12345"
    
    // Function declarations
    int insert_into_database(char *stock_name, int stock_quantity);
    void redirect_to_profile();
    
    // Entry point
    int main() {
      // Variables
      char stock_name[20];
      int stock_quantity;
    
      // Get input from user
      printf("Enter the stock name: ");
      scanf("%s", stock_name);
      printf("Enter the quantity of %s: ", stock_name);
      scanf("%d", &stock_quantity);
    
      // Insert into database
      insert_into_database(stock_name, stock_quantity);
    
      // Redirect to profile page
      redirect_to_profile();
    }
    
    // Function definitions
    int insert_into_database(char *stock_name, int stock_quantity) {
      sqlite3 *db;
      char *error_message = 0;
      char sql[100];
    
      // Open database
      int rc = sqlite3_open(SQLITE_DB, &db);
    
      if (rc != SQLITE_OK) {
        fprintf(stderr, "Error opening database: %s\n", error_message);
        sqlite3_close(db);
        return 1;
      }
    
      // Insert into table
      sprintf(sql, "INSERT INTO %s (stock_name, stock_quantity) VALUES ('%s', '%d')", SQLITE_TABLE, stock_name, stock_quantity);
      rc = sqlite3_exec(db, sql, 0, 0, &error_message);
    
      if (rc != SQLITE_OK) {
        fprintf(stderr, "Error inserting into table: %s\n", error_message);
        sqlite3_free(error_message);
        sqlite3_close(db);
        return 1;
      }
    
      // Close database
      rc = sqlite3_close(db);
    
      if (rc != SQLITE_OK) {
        fprintf(stderr, "Error closing database: %s\n", error_message);
        return 1;
      }
    
      return 0;
    }
    
    void redirect_to_profile() {
      printf("Location: /users/%s", USERNAME);
    }