#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            buy_function(stock_name);
        } else {
            fprintf(stderr, "Failed to insert into database\n");
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) == SQLITE_OK) {
        char create_table_sql[] = "CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY, name TEXT, quantity INTEGER);";
        sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);

        buy_stock(db, "AAPL", 10);
        
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    return 0;
}