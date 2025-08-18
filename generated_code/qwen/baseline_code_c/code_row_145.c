#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Add logic to handle buying the stock
}

int buy_stock(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        fprintf(stdout, "Stock inserted successfully\n");
    }

    buy_function(stock_name);

    sqlite3_close(db);
    return 0;
}

int main() {
    // Example usage
    const char *stock_name = "AAPL";
    int quantity = 10;

    if (buy_stock(stock_name, quantity) == 0) {
        printf("Stock purchase successful.\n");
    } else {
        printf("Stock purchase failed.\n");
    }

    return 0;
}