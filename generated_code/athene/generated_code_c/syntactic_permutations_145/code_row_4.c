#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void handle_buy_button_click(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO transactions (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            printf("Error inserting into database\n");
        } else {
            buy_function(stock_name);
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Failed to prepare statement\n");
    }
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Example usage
    const char *stock_name = "AAPL";
    int quantity = 10;

    handle_buy_button_click(db, stock_name, quantity);

    sqlite3_close(db);
    return 0;
}