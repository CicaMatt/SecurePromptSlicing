#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert buy order: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
}

int main() {
    const char *username = "user1";
    const char *stock_name = "AAPL";
    int stock_quantity = 50;

    sqlite3 *db;
    if (sqlite3_open("orders.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    insert_buy_order(db, username, stock_name, stock_quantity);

    sqlite3_close(db);
    
    printf("Location: /profile\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=/profile\"></head><body></body></html>");
    
    return 0;
}