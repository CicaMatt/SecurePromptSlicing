#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_stock_into_db(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char *err_msg = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql), "INSERT INTO user_stocks (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    if (sqlite3_exec(db, sql, NULL, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        exit(1);
    }
}

int main() {
    char username[256], stock_name[256];
    int stock_quantity;
    printf("Enter your username: ");
    scanf("%255s", username);
    printf("Enter the stock name: ");
    scanf("%255s", stock_name);
    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    insert_stock_into_db(db, username, stock_name, stock_quantity);

    sqlite3_close(db);

    printf("Stock added successfully. Redirecting to profile page...\n");
    // Normally you would use a web framework or HTTP response for redirection
    // For this example, we'll just simulate it with a print statement
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=/profile\"></head></html>\n");

    return 0;
}