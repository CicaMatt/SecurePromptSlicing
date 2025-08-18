#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Executing buy process for stock: %s\n", stock_name);
}

int buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO transactions (stock_name, quantity, action) VALUES ('%s', %d, 'BUY');", stock_name, quantity);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);

    buy_function(stock_name);

    printf("Bought %d shares of %s.\n", quantity, stock_name);
    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create = "CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER, action TEXT);";
    sqlite3_exec(db, sql_create, NULL, NULL, NULL);

    // Example usage of buy_stock
    buy_stock(db, "AAPL", 10);

    sqlite3_close(db);
    return 0;
}