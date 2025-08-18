#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    sqlite3_exec(db, sql, NULL, NULL, NULL);
}

int main() {
    char username[100], stock_name[100];
    int stock_quantity;
    
    printf("Enter your username: ");
    scanf("%99s", username);

    printf("Enter the stock name: ");
    scanf("%99s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    insert_buy_order(db, username, stock_name, stock_quantity);

    sqlite3_close(db);

    printf("Buy order placed successfully.\n");
    printf("Redirecting to profile page...\n");

    // Simulate redirection (in a real application, this would be handled by the web server)
    system("echo 'Profile Page'");

    return 0;
}