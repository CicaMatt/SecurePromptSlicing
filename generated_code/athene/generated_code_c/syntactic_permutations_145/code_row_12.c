#include <stdio.h>
#include <sqlite3.h>

void buy_function(int stock_id, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql = "INSERT INTO stocks (stock_id, quantity) VALUES (?, ?);";

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, stock_id);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", err_msg);
    } else {
        printf("Stock bought successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_stock(int stock_id, int quantity) {
    buy_function(stock_id, quantity);
}