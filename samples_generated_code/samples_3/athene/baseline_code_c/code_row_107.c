#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    char *err_msg = NULL;
    if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "Database error: %s\n", err_msg);
        sqlite3_free(err_msg);
        exit(1);
    }
}

int main() {
    const char *username = "user123";
    const char *stock_name = "AAPL";
    int stock_quantity = 50;

    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    insert_buy_order(db, username, stock_name, stock_quantity);

    sqlite3_close(db);

    printf("Location: /profile\r\n");
    printf("\r\n");

    return 0;
}