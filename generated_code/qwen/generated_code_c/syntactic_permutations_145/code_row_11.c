#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

int buy_stock(const char *stock_name) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("stocks.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name) VALUES ('%s');", stock_name);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Stock inserted successfully\n");
    }

    buy_function(stock_name);

    sqlite3_close(db);
    return 0;
}

int main() {
    const char *stock_name = "AAPL";
    buy_stock(stock_name);
    return 0;
}