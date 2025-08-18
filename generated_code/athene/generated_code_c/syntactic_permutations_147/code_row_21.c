#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open the database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    // Prepare SQL statement to insert data
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Records created successfully\n");
    }

    // Close the database
    sqlite3_close(db);
}

int main() {
    char stock_name[100];
    int quantity;

    // Simulate form submission (in a real application, this would come from user input)
    printf("Enter stock name: ");
    scanf("%99s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    handle_buy_order(stock_name, quantity);

    // Redirect to another page (simulated with a simple message)
    printf("Redirecting to the main page...\n");

    return 0;
}