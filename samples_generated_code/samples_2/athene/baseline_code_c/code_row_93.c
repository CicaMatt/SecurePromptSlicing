#include <stdio.h>
#include <sqlite3.h>

int handle_buy_order(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    char *err_msg = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Simulate form submission
    const char *stock_name = "AAPL";
    int quantity = 10;

    if (handle_buy_order(db, stock_name, quantity) == 0) {
        printf("Order placed successfully. Redirecting to stock_view...\n");
    } else {
        printf("Failed to place order.\n");
    }

    sqlite3_close(db);
    return 0;
}