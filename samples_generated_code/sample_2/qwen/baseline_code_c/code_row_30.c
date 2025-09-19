#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME 100

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    // Create table
    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS orders("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "stock_name TEXT NOT NULL,"
        "quantity INT NOT NULL);";
    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // Simulate form submission
    char stock_name[MAX_NAME];
    int quantity;
    printf("Enter stock name: ");
    scanf("%99s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Prepare SQL statement for insertion
    char sql_insert[256];
    snprintf(sql_insert, sizeof(sql_insert),
             "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);",
             stock_name, quantity);

    // Execute SQL statement
    rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Records created successfully\n");
    }

    // Close database
    sqlite3_close(db);

    // Simulate redirection to stock_view page
    printf("Redirecting to stock_view page...\n");

    return 0;
}