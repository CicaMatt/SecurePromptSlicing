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
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter stock name: ");
    scanf("%49s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    sqlite3 *db;
    if (sqlite3_open("example.db", &db) == SQLITE_OK) {
        insert_buy_order(db, username, stock_name, stock_quantity);
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Can't open database\n");
        return 1;
    }

    printf("Buy order placed successfully. Redirecting to profile page...\n");

    // Simulate redirection
    system("echo 'Profile Page'");
    return 0;
}