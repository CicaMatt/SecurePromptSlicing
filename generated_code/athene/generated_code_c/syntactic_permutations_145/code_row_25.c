#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name);

void buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        buy_function(stock_name);
    }

    sqlite3_finalize(stmt);
}

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}