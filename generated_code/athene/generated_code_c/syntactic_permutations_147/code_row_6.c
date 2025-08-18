#include <stdio.h>
#include <sqlite3.h>

void handle_buy_order(int quantity) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char *sql = "INSERT INTO orders (quantity) VALUES (?);";
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
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Data inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    int quantity;
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    handle_buy_order(quantity);

    printf("Redirecting to stock_view page...\n");
    return 0;
}