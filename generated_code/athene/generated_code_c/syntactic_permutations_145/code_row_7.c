#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

int buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO transactions (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
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
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Example call to buy_stock
    const char *stock_name = "AAPL";
    int quantity = 10;
    if (buy_stock(db, stock_name, quantity) != 0) {
        fprintf(stderr, "Failed to buy stock\n");
    } else {
        printf("Stock bought successfully\n");
    }

    sqlite3_close(db);
    return 0;
}