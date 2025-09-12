#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void buy_function(const char *stock_name) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks(stock_name, quantity) VALUES('%s', 1);", stock_name);

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Stock %s inserted successfully.\n", stock_name);
    }

    // Close database
    sqlite3_close(db);
}

void buy_stock(const char *stock_name, int quantity) {
    for (int i = 0; i < quantity; ++i) {
        buy_function(stock_name);
    }
}

int main() {
    // Create a database and table if they do not exist
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = 
        "CREATE TABLE IF NOT EXISTS stocks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "stock_name TEXT NOT NULL,"
        "quantity INTEGER DEFAULT 0);";

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Example usage
    buy_stock("AAPL", 5);

    sqlite3_close(db);
    return 0;
}