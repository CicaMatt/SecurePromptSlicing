#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            buy_function(stock_name);
        }
    }
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Database error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table if not exists
    const char *sql = "CREATE TABLE IF NOT EXISTS stocks (name TEXT, quantity INTEGER);";
    sqlite3_exec(db, sql, NULL, NULL, NULL);

    // Example usage of buy_stock
    buy_stock(db, "AAPL", 100);

    sqlite3_close(db);
    return 0;
}