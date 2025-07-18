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
