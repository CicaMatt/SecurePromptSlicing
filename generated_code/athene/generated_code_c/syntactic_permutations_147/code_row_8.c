#include <stdio.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name) {
    sqlite3 *db;
    int rc;

    // Open database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char *sql = "INSERT INTO Orders (StockName) VALUES (?);";
    sqlite3_stmt *stmt;

    // Prepare SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind the stock name
    rc = sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Bind error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Step error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Stock order inserted successfully.\n");
    }

    // Finalize and close
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char stock_name[100];
    
    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    handle_buy_order(stock_name);

    printf("Redirecting to stock_view page...\n");

    return 0;
}