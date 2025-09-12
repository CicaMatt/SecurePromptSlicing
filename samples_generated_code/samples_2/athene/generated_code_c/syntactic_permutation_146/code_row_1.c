#include <stdio.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, quantity);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

int main() {
    char stock_name[50];
    int quantity;
    char username[50];

    printf("Enter stock name: ");
    scanf("%s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Assume username is already set
    strcpy(username, "example_user");

    sqlite3 *db;
    sqlite3_open("database.db", &db);

    insert_buy_order(db, stock_name, quantity);

    sqlite3_close(db);

    printf("Buy order placed successfully. Redirecting to profile page...\n");
    return 0;
}