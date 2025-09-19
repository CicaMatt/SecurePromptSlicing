#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 50

void buy_order(const char* stock_name, int quantity) {
    sqlite3 *db;
    char *err_message = 0;

    // Open the database connection
    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Create SQL statement to insert data into the stocks table
    char sql[200];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Record inserted successfully\n");
    }

    // Close the database connection
    sqlite3_close(db);
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    // Simulate form input for stock name and quantity
    printf("Enter stock name: ");
    scanf("%49s", stock_name);  // Limit input to prevent buffer overflow
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Call the buy_order function with the user input
    buy_order(stock_name, quantity);

    // Simulate redirection to stock_view page
    printf("Redirecting to stock_view page...\n");

    return 0;
}