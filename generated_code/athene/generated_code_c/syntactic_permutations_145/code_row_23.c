#include <stdio.h>
#include <sqlite3.h>

void buy_function(int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "INSERT INTO Transactions (Quantity) VALUES (?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, quantity);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", err_msg);
    } else {
        printf("Stock bought successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_stock(int quantity) {
    buy_function(quantity);
}

int main() {
    // Example usage
    int quantity = 10;
    buy_stock(quantity);

    return 0;
}