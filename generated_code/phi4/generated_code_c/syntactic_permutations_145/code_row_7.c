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
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    } else {
        printf("Opened database successfully\n");
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name) VALUES ('%s');", stock_name);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Record created successfully\n");
    }

    sqlite3_close(db);
}

void buy_stock(const char *stock_name, int quantity) {
    buy_function(stock_name);

    // Assume additional logic for handling quantity if needed
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;

    // Create database and table (if not exists)
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        printf("Opened database successfully\n");
    }

    char *sql = "CREATE TABLE IF NOT EXISTS stocks ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Table created successfully\n");
    }

    buy_stock(stock_name, quantity);

    sqlite3_close(db);

    return 0;
}