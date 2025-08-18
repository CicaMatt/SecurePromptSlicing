#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (username, stock_name, quantity, type) VALUES ('%s', '%s', %d, 'buy');", username, stock_name, quantity);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

int main() {
    char stock_name[50];
    int quantity;
    const char *username = "user1"; // Assuming username is set elsewhere in the application

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);
    
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    sqlite3 *db;
    if (sqlite3_open("example.db", &db) == SQLITE_OK) {
        insert_buy_order(db, stock_name, quantity);
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Failed to open database\n");
        return 1;
    }

    printf("Buy order placed successfully. Redirecting to profile page...\n");
    // For actual redirection in a web application, you would use:
    // printf("Location: /profile\n");
    // exit(0);
    
    return 0;
}