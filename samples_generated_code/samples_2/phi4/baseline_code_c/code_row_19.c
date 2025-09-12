#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void buy_function(const char* stock_name) {
    sqlite3 *db;
    char *err_msg = NULL;
    int rc;

    rc = sqlite3_open("stocks.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks(stock_name) VALUES('%s')", stock_name);

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Record inserted successfully.\n");
    }

    sqlite3_close(db);
}

void buy_stock(const char* stock_name, int quantity) {
    // Here we assume the form has already processed and validated `stock_name` and `quantity`
    buy_function(stock_name);
}

int main() {
    const char *sql = "CREATE TABLE IF NOT EXISTS stocks ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "stock_name TEXT NOT NULL);";

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("stocks.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return(1);
    } 

    // Example usage
    buy_stock("AAPL", 10);

    sqlite3_close(db);
    return 0;
}