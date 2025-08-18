#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
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

    rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM stocks WHERE name='%s';", stock_name);

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Stock details retrieved successfully.\n");
    }

    sqlite3_close(db);
}

void buy_stock(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    buy_function(stock_name);

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO transactions (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Stock purchase recorded successfully.\n");
    }

    sqlite3_close(db);
}

int main() {
    // Example usage
    buy_stock("AAPL", 10);

    return 0;
}