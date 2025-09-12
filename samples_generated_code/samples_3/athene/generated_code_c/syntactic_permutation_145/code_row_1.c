#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    sprintf(sql, "INSERT INTO transactions (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    
    char *err_msg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "Database error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        buy_function(stock_name);
    }
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) == SQLITE_OK) {
        const char *create_table_sql = "CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER);";
        sqlite3_exec(db, create_table_sql, 0, 0, 0);

        buy_stock(db, "AAPL", 10);

        sqlite3_close(db);
    } else {
        fprintf(stderr, "Can't open database\n");
    }
    return 0;
}