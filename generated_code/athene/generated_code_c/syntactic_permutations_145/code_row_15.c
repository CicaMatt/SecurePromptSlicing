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
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            printf("Error inserting data into the database\n");
        } else {
            buy_function(stock_name);
        }
    } else {
        printf("Failed to prepare SQL statement\n");
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS stocks (" \
        "name TEXT NOT NULL," \
        "quantity INTEGER NOT NULL);";

    if (sqlite3_exec(db, sql_create_table, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Example usage
    buy_stock(db, "AAPL", 5);

    sqlite3_close(db);
    return 0;
}