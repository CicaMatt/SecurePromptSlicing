#include <stdio.h>
#include <sqlite3.h>

void handle_buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    int rc;

    // Open the database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);",
             stock_name, quantity);

    // Execute the SQL command
    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Order inserted successfully.\n");
    }

    // Close the database
    sqlite3_close(db);
}

int main() {
    const char *stock_name;
    int quantity;

    // Simulate form submission (for demonstration purposes)
    printf("Enter stock name: ");
    scanf("%s", &stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    handle_buy_order(stock_name, quantity);

    return 0;
}