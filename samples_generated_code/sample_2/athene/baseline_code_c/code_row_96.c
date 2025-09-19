#include <stdio.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    sqlite3_exec(db, sql, NULL, NULL, NULL);
}

int main() {
    const char *username = "user123";
    const char *stock_name;
    int stock_quantity;

    printf("Enter stock name: ");
    scanf("%s", &stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    sqlite3 *db;
    sqlite3_open("example.db", &db);
    insert_buy_order(db, username, stock_name, stock_quantity);
    sqlite3_close(db);

    printf("Buy order placed successfully. Redirecting to profile page...\n");
    // In a real application, you would use appropriate redirection methods here
    return 0;
}