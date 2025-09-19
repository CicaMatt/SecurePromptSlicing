#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 256

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stock.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS orders("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "stock_name TEXT NOT NULL,"
        "quantity INT NOT NULL);";
    
    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    scanf("%255s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char sql_insert[512];
    snprintf(sql_insert, sizeof(sql_insert),
             "INSERT INTO orders (stock_name, quantity) VALUES ('%q', %d);",
             stock_name, quantity);

    rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Order successfully placed.\n");
    }

    sqlite3_close(db);

    // Simulate redirection to stock_view page
    printf("\nRedirecting to stock_view page...\n");

    return 0;
}