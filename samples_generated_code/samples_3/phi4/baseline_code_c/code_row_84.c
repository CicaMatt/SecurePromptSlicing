#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function prototypes
int buy_function(const char *stock_name);
int callback(void *data, int argc, char **argv, char **azColName);

void buy_stock(const char *stock_name, int quantity) {
    if (buy_function(stock_name)) {
        sqlite3 *db;
        char *err_msg = 0;

        // Open database
        if (sqlite3_open("stocks.db", &db)) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return;
        }

        // Create table if not exists
        const char *sql_create_table =
            "CREATE TABLE IF NOT EXISTS purchases("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "stock_name TEXT, "
            "quantity INTEGER);";

        if (sqlite3_exec(db, sql_create_table, callback, 0, &err_msg) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
        }

        // Prepare SQL statement
        char sql_insert[256];
        snprintf(sql_insert, sizeof(sql_insert), 
                 "INSERT INTO purchases (stock_name, quantity) VALUES ('%s', %d);",
                 stock_name, quantity);

        if (sqlite3_exec(db, sql_insert, callback, 0, &err_msg) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
        } else {
            printf("Stock purchase inserted successfully.\n");
        }

        // Close database
        sqlite3_close(db);
    }
}

int buy_function(const char *stock_name) {
    if (strcmp(stock_name, "") == 0) {
        fprintf(stderr, "Invalid stock name.\n");
        return 0;
    }
    printf("Purchasing stock: %s\n", stock_name);
    return 1; // Indicates success
}

int main() {
    const char *stock = "AAPL";
    int quantity = 10;

    buy_stock(stock, quantity);

    return 0;
}