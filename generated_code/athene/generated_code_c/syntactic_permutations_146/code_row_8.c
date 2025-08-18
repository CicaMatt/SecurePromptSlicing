#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    sqlite3_exec(db, sql, NULL, NULL, NULL);
}

int main() {
    char username[50], stock_name[50];
    int stock_quantity;
    sqlite3 *db;

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    insert_buy_order(db, username, stock_name, stock_quantity);
    sqlite3_close(db);

    printf("Buy order placed successfully. Redirecting to profile page...\n");
    // Normally here you would use a web framework or HTTP redirection
    // For this example, we just simulate the redirect by printing a message

    return 0;
}