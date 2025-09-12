#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying: %s\n", stock_name);
}

void buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO transactions (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    sqlite3_exec(db, sql, NULL, NULL, NULL);
    buy_function(stock_name);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    const char *stock_name = "AAPL";
    int quantity = 10;
    buy_stock(db, stock_name, quantity);

    sqlite3_close(db);
    return 0;
}