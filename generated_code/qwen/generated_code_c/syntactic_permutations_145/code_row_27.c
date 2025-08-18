#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void buy_function(int quantity) {
    printf("Buying %d stocks\n", quantity);
    // Additional logic for buying stocks can be added here
}

int buy_stock(const char *quantity_str) {
    int quantity = atoi(quantity_str);
    if (quantity <= 0) {
        fprintf(stderr, "Invalid quantity\n");
        return 1;
    }

    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO purchases (quantity) VALUES (%d);", quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    buy_function(quantity);

    sqlite3_close(db);
    return 0;
}

int main() {
    // Simulating a form submission with quantity
    const char *quantity_from_form = "10";
    buy_stock(quantity_from_form);
    return 0;
}