#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sqlite3.h>

    void insert_user_message_in_db(const char *username, const char *message) {
      sqlite3 *db;
      char *error_message = 0;
      int result;
    
      result = sqlite3_open("main.db", &db);
      
      if (result != SQLITE_OK) {
        printf("Failed to open database\n");
        exit(1);
      }
    
      char *sql = "INSERT INTO messages (username, message) VALUES ('%s', '%s');";
      sprintf(sql, username, message);
      
      result = sqlite3_exec(db, sql, 0, 0, &error_message);
      
      if (result != SQLITE_OK) {
        printf("Failed to insert data into database\n");
        exit(1);
      }
    
      sqlite3_close(db);
    }
  
    void post() {
      const char *username = get_string("username");
      const char *message = get_string("message");
      
      insert_user_message_in_db(username, message);
    
      redirect("/main.html");
    }