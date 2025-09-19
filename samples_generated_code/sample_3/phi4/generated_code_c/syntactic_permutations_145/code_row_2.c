#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void buy_function(const char *stock_name) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *sqlInsert = "INSERT INTO stocks (stock_name) VALUES (?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Stock '%s' added successfully.\n", stock_name);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_stock(const char *stock_name, int quantity) {
    // Call the buy_function with the stock name
    buy_function(stock_name);

    // Additional logic to handle quantity can be implemented here if needed
}

int main() {
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS stocks ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "stock_name TEXT NOT NULL);";

    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    rc = sqlite3_exec(db, createTableSQL, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Table created successfully.\n");
    }

    // Example usage of buy_stock function
    buy_stock("AAPL", 10);

    sqlite3_close(db);
    return 0;
}