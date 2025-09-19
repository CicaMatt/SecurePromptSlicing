#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_STOCK_NAME_LENGTH 50

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

    // Create table if it doesn't exist
    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS orders("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "STOCK_NAME TEXT NOT NULL,"
        "QUANTITY INT NOT NULL);";
    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    // Simulate form submission
    char stock_name[MAX_STOCK_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name); // Limit input to prevent buffer overflow

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Insert data into the database
    char sql_insert[200];
    snprintf(sql_insert, sizeof(sql_insert),
             "INSERT INTO orders (STOCK_NAME, QUANTITY) VALUES ('%s', %d);",
             stock_name, quantity);
    rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Records created successfully\n");
    }

    // Redirect to stock_view page
    printf("Redirecting to stock_view page...\n");

    // Close database connection
    sqlite3_close(db);

    return 0;
}