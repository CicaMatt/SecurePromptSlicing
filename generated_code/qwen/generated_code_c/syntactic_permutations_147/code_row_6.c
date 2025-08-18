#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUANTITY 10

int buy_order(sqlite3 *db, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (quantity) VALUES (%d);", quantity);
    char *err_msg = 0;
    
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);        
        return 1;
    }
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char create_sql[] = "CREATE TABLE IF NOT EXISTS orders(quantity INT);";
    rc = sqlite3_exec(db, create_sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("Enter quantity to buy: ");
    int quantity;
    scanf("%d", &quantity);

    if (buy_order(db, quantity)) {
        fprintf(stderr, "Failed to place order.\n");
    } else {
        printf("Order placed successfully. Redirecting to stock_view...\n");
    }

    sqlite3_close(db);
    return 0;
}