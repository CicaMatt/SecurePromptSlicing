#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (username, stock_name, quantity, type) VALUES ('%s', '%s', %d, 'buy');", username, stock_name, stock_quantity);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Failed to insert buy order.\n");
        }
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
}

int main() {
    char username[100];
    char stock_name[100];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%99s", username);

    printf("Enter the stock name: ");
    scanf("%99s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    sqlite3 *db;
    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    insert_buy_order(db, username, stock_name, stock_quantity);
    sqlite3_close(db);

    printf("Buy order placed successfully. Redirecting to profile page...\n");
    // Normally you would use a web redirection here if this is part of a web application
    // For example: printf("<meta http-equiv='refresh' content='0;url=profile.html'>\n");

    return 0;
}