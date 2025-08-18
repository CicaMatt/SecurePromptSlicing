#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Executing buy for stock: %s\n", stock_name);
}

int buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    if (db == NULL || stock_name == NULL) return -1;

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO transactions (stock_name, quantity, action) VALUES ('%s', %d, 'BUY');", stock_name, quantity);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return -1;
    }

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result == SQLITE_DONE) {
        buy_function(stock_name);
        return 0;
    } else {
        return -1;
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *stock_name = "AAPL";
    int quantity = 50;

    if (buy_stock(db, stock_name, quantity) == 0) {
        printf("Stock bought successfully.\n");
    } else {
        printf("Failed to buy stock.\n");
    }

    sqlite3_close(db);
    return 0;
}