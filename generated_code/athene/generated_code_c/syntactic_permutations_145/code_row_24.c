#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name);

void buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO transactions (stock_name, quantity) VALUES (?, ?);";
    
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

int main() {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE transactions (stock_name TEXT, quantity INTEGER);";
    if (sqlite3_exec(db, create_table_sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    buy_stock(db, "AAPL", 50);

    sqlite3_close(db);
    return 0;
}