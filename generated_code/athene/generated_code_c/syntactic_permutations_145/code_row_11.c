#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(sqlite3 *db, const char *stock_name) {
    const char *sql = "INSERT INTO stocks (name) VALUES (?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data\n");
    } else {
        printf("Stock bought successfully: %s\n", stock_name);
        buy_function(stock_name);
    }
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);";
    sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);

    // Simulate form input
    const char *stock_name = "AAPL";

    buy_stock(db, stock_name);

    sqlite3_close(db);
    return 0;
}