#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
}

int main() {
    const char *stock_name = "AAPL"; // Example stock name
    int quantity = 10; // Example quantity

    handle_buy_order(stock_name, quantity);

    printf("Order placed successfully. Redirecting...\n");

    return 0;
}