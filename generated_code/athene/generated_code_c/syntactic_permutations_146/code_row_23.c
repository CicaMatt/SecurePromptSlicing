#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insertBuyOrder(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            printf("Error inserting buy order.\n");
        }
    } else {
        printf("Failed to prepare SQL statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
}

int main() {
    char username[100], stock_name[100];
    int stock_quantity;
    sqlite3 *db;

    // Simulate user input
    printf("Enter your username: ");
    scanf("%99s", username);
    printf("Enter the stock name: ");
    scanf("%99s", stock_name);
    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    // Open database connection
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Insert buy order into the database
    insertBuyOrder(db, username, stock_name, stock_quantity);

    // Close database connection
    sqlite3_close(db);

    // Redirect user (simulated with a simple message)
    printf("Redirecting to the next page...\n");

    return 0;
}