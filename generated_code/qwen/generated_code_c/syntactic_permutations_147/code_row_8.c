#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 256

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void insertStockIntoDatabase(const char* stockName) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char* sql = "INSERT INTO stocks (name) VALUES (?);";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, stockName, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Stock inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char stockName[MAX_NAME_LENGTH];

    printf("Enter the stock name: ");
    if (fgets(stockName, sizeof(stockName), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(stockName);
        if (len > 0 && stockName[len - 1] == '\n') {
            stockName[len - 1] = '\0';
        }
    }

    insertStockIntoDatabase(stockName);

    printf("Redirecting to stock_view page...\n");

    return 0;
}