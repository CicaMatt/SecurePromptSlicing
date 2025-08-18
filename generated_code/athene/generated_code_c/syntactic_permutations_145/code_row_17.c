#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

int buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    sprintf(sql, "INSERT INTO transactions (stock_name, quantity, type) VALUES ('%s', %d, 'buy');", stock_name, quantity);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error executing statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);

    buy_function(stock_name);

    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table for transactions
    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "stock_name TEXT NOT NULL,"
        "quantity INTEGER NOT NULL,"
        "type TEXT NOT NULL);";

    sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);

    // Example call to buy_stock
    const char *stock_name = "AAPL";
    int quantity = 10;
    if (buy_stock(db, stock_name, quantity) != 0) {
        fprintf(stderr, "Failed to buy stock\n");
    }

    sqlite3_close(db);
    return 0;
}