#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

int buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    char *err_msg = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }

    buy_function(stock_name);

    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *stock_name = "AAPL";
    int quantity = 5;

    buy_stock(db, stock_name, quantity);

    sqlite3_close(db);
    return 0;
}