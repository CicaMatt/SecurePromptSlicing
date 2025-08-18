#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open the database (or create it if it doesn't exist)
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Create table if it does not exist
    const char *sql_create = "CREATE TABLE IF NOT EXISTS Orders (Name TEXT, Quantity INTEGER);";
    rc = sqlite3_exec(db, sql_create, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Simulate form submission
    char stock_name[50];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Insert data into the database
    char sql_insert[200];
    sprintf(sql_insert, "INSERT INTO Orders (Name, Quantity) VALUES ('%s', %d);", stock_name, quantity);
    rc = sqlite3_exec(db, sql_insert, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Redirect to stock_view page
    printf("Data inserted successfully. Redirecting to stock_view...\n");

    sqlite3_close(db);
    return 0;
}