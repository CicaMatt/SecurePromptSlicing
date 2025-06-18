#include <stdlib.h> 
    #include <stdio.h>  
    #include "sqlite3.h"  
    
    #define DATABASE_FILENAME "database.db" 
    #define USERID_ENVVAR "USERID" 
    
    bool is_moderator() {  
       // Check if environment variable exists  
       const char *userid = getenv(USERID_ENVVAR);  
       if (userid == NULL) {  
          fprintf(stderr, "%s not set\n", USERID_ENVVAR);  
          return false; 
       } 
       
       // Open database connection 
       sqlite3 *db;  
       int rc = sqlite3_open(DATABASE_FILENAME, &db);  
       if (rc != SQLITE_OK) {  
          fprintf(stderr, "Unable to open %s: %s\n", DATABASE_FILENAME, sqlite3_errmsg(db));  
          return false; 
       } 
    
       // Prepare query statement and bind userid parameter 
       char *query = "SELECT is_moderator FROM users WHERE id=?";  
       sqlite3_stmt *stmt;  
       rc = sqlite3_prepare(db, query, -1, &stmt, NULL); 
       if (rc != SQLITE_OK) {  
          fprintf(stderr, "Unable to prepare statement: %s\n", sqlite3_errmsg(db));  
          sqlite3_close(db); 
          return false; 
       } 
        rc = sqlite3_bind_text(stmt, 1, userid, -1, SQLITE_STATIC); 
        if (rc != SQLITE_OK) {  
           fprintf(stderr, "Unable to bind parameter: %s\n", sqlite3_errmsg(db));  
           sqlite3_close(db); 
           return false; 
       } 
    
       // Step through the result set and check for is_moderator 
       int step = sqlite3_step(stmt); 
       if (step != SQLITE_ROW) {  
          fprintf(stderr, "Unable to fetch results: %s\n", sqlite3_errmsg(db));  
          sqlite3_close(db); 
          return false; 
       } 
    
       // Get the value and close database connection 
       bool isModerator = sqlite3_column_int(stmt, 0) != 0; 
       sqlite3_finalize(stmt);  
       sqlite3_close(db); 
    
       return isModerator; 
    }