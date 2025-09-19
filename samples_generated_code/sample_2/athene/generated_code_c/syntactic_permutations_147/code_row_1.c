#include <stdio.h>
#include <sqlite3.h>

void handle_form_submission() {
    char stock_name[50];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    sqlite3 *db;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[200];
    sprintf(sql, "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Order inserted successfully.\n");
    }

    sqlite3_close(db);

    // Redirect to stock_view page
    printf("Redirecting to stock_view...\n");
}

int main() {
    handle_form_submission();
    return 0;
}