#include <stdio.h>
    #include <stdlib.h>
    #include <sqlite3.h>
    
    void buy_order(char *stockName, int quantity) {
        sqlite3 *db;
        char *errMsg = 0;
        char sql[1024];
        int rc;
        sprintf(sql, "insert into stock (name, quantity) values ('%s', %d)", stockName, quantity);
        rc = sqlite3_open("stock.db", &db);
        if (rc != SQLITE_OK) {
            printf("%s\n", errMsg);
            exit(1);
        }
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            printf("%s\n", errMsg);
            sqlite3_free(errMsg);
            exit(1);
        }
    }
    
    int main() {
        buy_order("ABC", 250);
        return 0;
    }

### Explanation:

This code defines a function that takes two arguments: stockName and quantity. The function uses the sqlite3 library to insert the data into a database file called stock.db. The main function calls the buy_order function with the values "ABC" and 250 as its arguments.