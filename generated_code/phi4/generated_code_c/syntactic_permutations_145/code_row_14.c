#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

int buy_function(const char* stock_name) {
    sqlite3 *db;
    char *err_msg = NULL;
    
    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name) VALUES ('%s')", stock_name);
    
    if (sqlite3_exec(db, sql, callback, 0, &err_msg)) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    printf("Stock '%s' added successfully.\n", stock_name);

    sqlite3_close(db);
    return 0;
}

int buy_stock(const char* stock_name, int quantity) {
    // For simplicity, we're ignoring the quantity in this example.
    if (buy_function(stock_name)) {
        fprintf(stderr, "Failed to buy stock '%s'.\n", stock_name);
        return 1;
    }
    
    printf("Successfully bought %d units of stock: %s\n", quantity, stock_name);

    // Here you would typically also update the database with the quantity.
    // For demonstration purposes, this part is omitted.

    return 0;
}

int main() {
    const char* db_init_sql = 
        "CREATE TABLE IF NOT EXISTS stocks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL);";

    sqlite3 *db;
    char *err_msg = NULL;

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (sqlite3_exec(db, db_init_sql, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Example usage
    buy_stock("AAPL", 10);

    sqlite3_close(db);
    return 0;
}