#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO purchases (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            printf("Error inserting data into the database\n");
        }
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);

    buy_function(stock_name);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Example call to buy_stock
    buy_stock(db, "AAPL", 10);

    sqlite3_close(db);
    return 0;
}