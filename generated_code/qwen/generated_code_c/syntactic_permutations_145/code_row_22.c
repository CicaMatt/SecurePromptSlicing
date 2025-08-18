#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
    // Additional logic for buying the stock can be added here
}

int buy_stock(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_message = 0;

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    if (sqlite3_exec(db, sql, 0, 0, &err_message) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    buy_function(stock_name);

    sqlite3_close(db);
    return 0;
}

int main() {
    const char *stock_name = "ExampleCorp";
    int quantity = 10;

    if (buy_stock(stock_name, quantity)) {
        fprintf(stderr, "Error buying stock\n");
        return 1;
    }

    printf("Stock bought successfully\n");
    return 0;
}