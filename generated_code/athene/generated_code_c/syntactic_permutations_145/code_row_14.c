#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying: %s\n", stock_name);
}

int buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return 1;
    }
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    buy_function(stock_name);
    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    char create_table_sql[] = "CREATE TABLE IF NOT EXISTS stocks (name TEXT, quantity INTEGER);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);
    
    const char *stock_name = "AAPL";
    int quantity = 10;
    if (buy_stock(db, stock_name, quantity) != 0) {
        fprintf(stderr, "Failed to buy stock\n");
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}