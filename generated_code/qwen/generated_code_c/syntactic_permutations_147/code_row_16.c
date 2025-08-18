#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 256

int insert_stock_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);",
             stock_name, quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    if (fgets(stock_name, sizeof(stock_name), stdin) != NULL) {
        // Remove newline character from fgets
        stock_name[strcspn(stock_name, "\n")] = 0;
    }

    printf("Enter quantity: ");
    if (scanf("%d", &quantity) != 1) {
        fprintf(stderr, "Invalid input for quantity\n");
        return 1;
    }

    if (insert_stock_order(stock_name, quantity) == 0) {
        printf("Order submitted successfully. Redirecting to stock_view page...\n");
    } else {
        printf("Failed to submit order.\n");
    }

    return 0;
}