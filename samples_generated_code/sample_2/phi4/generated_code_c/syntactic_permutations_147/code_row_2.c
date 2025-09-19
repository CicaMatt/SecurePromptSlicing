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

void insert_order(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    
    char *errMsg = NULL;
    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Order inserted successfully.\n");
    }
}

int main() {
    sqlite3 *db;
    char *errMsg = NULL;

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS orders("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "stock_name TEXT NOT NULL,"
        "quantity INTEGER NOT NULL);";

    if (sqlite3_exec(db, sqlCreateTable, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    char stock_name[50];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    insert_order(db, stock_name, quantity);

    // Simulate redirection by viewing the orders
    const char *sqlSelectAll = "SELECT * FROM orders;";
    
    if (sqlite3_exec(db, sqlSelectAll, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return 0;
}
