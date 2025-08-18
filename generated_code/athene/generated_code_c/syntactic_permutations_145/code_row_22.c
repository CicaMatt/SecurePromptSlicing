#include <stdio.h>
#include <sqlite3.h>

void buy_function(char *stock_name) {
    printf("Processing buy for stock: %s\n", stock_name);
}

void buy_stock(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql_stmt = "INSERT INTO stocks (name, quantity) VALUES (?, ?);";

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data\n");
    } else {
        printf("Stock '%s' bought with quantity %d\n", stock_name, quantity);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    buy_function(stock_name);
}

int main() {
    char stock_name[] = "AAPL";
    int quantity = 10;
    buy_stock(stock_name, quantity);
    return 0;
}