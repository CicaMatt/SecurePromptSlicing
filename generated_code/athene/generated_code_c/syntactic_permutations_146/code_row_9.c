#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    sprintf(sql, "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

int main() {
    char username[50], stock_name[50];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    sqlite3 *db;
    if (sqlite3_open("orders.db", &db) == SQLITE_OK) {
        insert_buy_order(db, username, stock_name, stock_quantity);
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Cannot open database.\n");
        return 1;
    }

    printf("Buy order placed successfully. Redirecting to profile page...\n");

    // Simulate redirection
    system("echo 'Profile Page'");
    
    return 0;
}