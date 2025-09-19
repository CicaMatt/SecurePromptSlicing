#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void insert_buy_order(const char *username, const char *stock_name, int stock_quantity) {
    sqlite3 *db;
    char *err_message = 0;

    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);",
             username, stock_name, stock_quantity);

    if (sqlite3_exec(db, sql, 0, 0, &err_message) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
}

int main() {
    char username[50];
    char stock_name[50];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    insert_buy_order(username, stock_name, stock_quantity);

    // Redirect to profile page (simulated by printing a message)
    printf("Redirecting to profile page...\n");

    return 0;
}