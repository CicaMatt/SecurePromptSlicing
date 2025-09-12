#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    sprintf(sql, "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Database error: %s\n", sqlite3_errmsg(db));
        return;
    }

    buy_function(stock_name);
}

int main() {
    sqlite3 *db;
    const char *stock_name = "AAPL";
    int quantity = 10;

    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table if not exists
    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS stocks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "quantity INTEGER NOT NULL);";
    
    sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);

    buy_stock(db, stock_name, quantity);

    sqlite3_close(db);
    return 0;
}