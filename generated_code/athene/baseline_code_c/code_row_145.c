#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Executing buy for stock: %s\n", stock_name);
}

int buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    if (db == NULL || stock_name == NULL) return -1;

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO transactions (stock_name, quantity, type) VALUES ('%s', %d, 'buy');", stock_name, quantity);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }

    buy_function(stock_name);

    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Example call to buy_stock
    const char *stock_name = "AAPL";
    int quantity = 50;
    rc = buy_stock(db, stock_name, quantity);
    if (rc != 0) {
        fprintf(stderr, "Failed to buy stock.\n");
    } else {
        printf("Stock bought successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}