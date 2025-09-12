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

void buy_function(int quantity) {
    sqlite3 *db;
    char *err_msg = NULL;
    
    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO purchases (quantity) VALUES (%d);", quantity);

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Purchase successfully recorded.\n");
    }

    sqlite3_close(db);
}

void buy_stock(int quantity) {
    buy_function(quantity);
}

int main() {
    int quantity;
    printf("Enter the stock quantity to purchase: ");
    scanf("%d", &quantity);

    buy_stock(quantity);

    return 0;
}