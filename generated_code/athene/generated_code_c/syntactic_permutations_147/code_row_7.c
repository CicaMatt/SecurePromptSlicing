#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    int rc;

    // Open the database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char *sql = "INSERT INTO Orders (StockName, Quantity) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind the parameters
    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void handle_user_input() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    // Redirect to stock_view page (simulated here)
    printf("Redirecting to stock_view...\n");
}

int main() {
    handle_user_input();
    return 0;
}