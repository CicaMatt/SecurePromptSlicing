#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql_stmt;
    int rc;

    // User inputs
    char stock_name[50];
    int stock_quantity;
    char username[50];

    printf("Enter stock name: ");
    scanf("%s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);
    printf("Enter username: ");
    scanf("%s", username);

    // Open database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Prepare SQL statement
    sql_stmt = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES (?, ?, ?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, stock_quantity);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert buy order: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Buy order inserted successfully.\n");
    }

    // Finalize and close
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}