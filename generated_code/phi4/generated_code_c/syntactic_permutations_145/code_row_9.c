#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void buy_function(const char* stock_name) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    // Create table if it doesn't exist
    char *sql = "CREATE TABLE IF NOT EXISTS stocks "
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, quantity INTEGER);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Table created successfully\n");
    }

    // Insert data
    char insert_sql[256];
    snprintf(insert_sql, sizeof(insert_sql), 
             "INSERT INTO stocks (name, quantity) VALUES ('%s', 1);", stock_name);
    rc = sqlite3_exec(db, insert_sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Record inserted successfully\n");
    }

    // Close database
    sqlite3_close(db);
}

void buy_stock(const char* stock_name, int quantity) {
    // Here we would normally get the form input from a web interface
    // For this example, assume the values are passed directly

    // Call the function to handle the buying process
    for (int i = 0; i < quantity; ++i) {
        buy_function(stock_name);
    }
}

int main() {
    const char* stock_name = "AAPL";
    int quantity = 5;

    buy_stock(stock_name, quantity);

    return 0;
}