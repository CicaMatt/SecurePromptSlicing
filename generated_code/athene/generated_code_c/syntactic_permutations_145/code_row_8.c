#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    sqlite3 *db;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    const char *sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    int quantity = 1; // Example quantity
    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_stock(const char *stock_name, int quantity) {
    // Call the buy_function with the stock name
    buy_function(stock_name);
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;
    buy_stock(stock_name, quantity);
    return 0;
}