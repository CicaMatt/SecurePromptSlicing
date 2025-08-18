#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 50

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void insert_buy_order(const char* stock_name, int quantity) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, callback, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter the stock name: ");
    if (scanf("%49s", stock_name) != 1) {
        fprintf(stderr, "Invalid input for stock name.\n");
        return 1;
    }

    printf("Enter the quantity: ");
    if (scanf("%d", &quantity) != 1 || quantity <= 0) {
        fprintf(stderr, "Invalid input for quantity.\n");
        return 1;
    }

    insert_buy_order(stock_name, quantity);

    printf("Redirecting to stock_view page...\n");

    return 0;
}