#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 100

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void insert_stock_order(const char* stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[256];

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Records created successfully\n");
    }

    sqlite3_close(db);
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    scanf("%s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    insert_stock_order(stock_name, quantity);

    // Simulate redirection to stock_view page
    printf("Redirecting to stock_view page...\n");

    return 0;
}