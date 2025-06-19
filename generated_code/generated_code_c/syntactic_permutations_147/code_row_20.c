#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sqlite3.h>
    
    int main() {
        sqlite3 *db;
        char *error_message = 0;
        const char *sql = "INSERT INTO buy_order (stock_name, quantity) VALUES (?1, ?2);";
        sqlite3_stmt *statement;
        
        // open a connection to the database
        int result = sqlite3_open("db/example.db", &db);
        if (result != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
        
        // prepare the insert statement
        result = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
        if (result != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
        
        // bind the parameters to the statement
        sqlite3_bind_text(statement, 1, "ABC", -1, SQLITE_STATIC);
        sqlite3_bind_int64(statement, 2, 25);
        
        // execute the insert statement
        result = sqlite3_step(statement);
        if (result != SQLITE_DONE) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
        
        // finalize the statement and close the connection
        sqlite3_finalize(statement);
        sqlite3_close(db);
        
        printf("Successfully inserted into database");
        
        return 0;
    }