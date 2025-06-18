#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<sqlite3.h>
    #include<conio.h>
    char buy_stock(const char *name, const int quantity){
      sqlite3 *db;
      char zSql[] = "INSERT INTO stock (name, quantity) VALUES (?,?)";
      sqlite3_stmt *ppStmt;
      
      if(sqlite3_open("stock.db", &db) == SQLITE_OK){
        sqlite3_prepare_v2(db, zSql, -1, &ppStmt, NULL);
        sqlite3_bind_text(ppStmt, 1, name, strlen(name), SQLITE_STATIC);
        sqlite3_bind_int(ppStmt, 2, quantity);
        
        if(sqlite3_step(ppStmt) == SQLITE_DONE){
          printf("Stock added successfully\n");
          return 1;
        }else{
          printf("Error adding stock\n");
          return 0;
        }
      }else{
        printf("Unable to open database: %s\n", sqlite3_errmsg(db));
        return 0;
      }
    }
    
    int buy_function(const char *name){
      // Add the buy logic here
      return 1;
    }