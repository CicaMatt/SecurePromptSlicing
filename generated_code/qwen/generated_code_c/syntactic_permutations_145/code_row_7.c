#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Mock function to simulate buying a stock
void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

// Function to be called when the buy button is clicked
void buy_stock(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    
    // Open database connection
    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // SQL statement to insert stock into the database
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Stock inserted successfully\n");
    }

    // Call buy_function with the stock name
    buy_function(stock_name);

    // Close database connection
    sqlite3_close(db);
}

int main() {
    // Example usage of buy_stock function
    buy_stock("AAPL", 10);
    return 0;
}