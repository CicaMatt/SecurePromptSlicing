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

void create_table(sqlite3 *db) {
    char *errMsg = NULL;
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS BUY_ORDERS("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "STOCK_NAME TEXT NOT NULL, "
        "QUANTITY INTEGER NOT NULL);";
    
    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Table created successfully or already exists.\n");
    }
}

void insert_order(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[200];
    snprintf(sql, sizeof(sql),
             "INSERT INTO BUY_ORDERS(STOCK_NAME, QUANTITY) VALUES ('%s', %d);",
             stock_name, quantity);
    
    char *errMsg = NULL;
    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Record inserted successfully.\n");
    }
}

void buy_order(sqlite3 *db) {
    char stock_name[100];
    int quantity;
    
    printf("Enter stock name: ");
    scanf("%99s", stock_name);
    
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    
    insert_order(db, stock_name, quantity);
}

void view_stock_orders(sqlite3 *db) {
    const char *sql = "SELECT * FROM BUY_ORDERS;";
    char *errMsg = NULL;
    
    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Stock orders viewed successfully.\n");
    }
}

int main() {
    sqlite3 *db;
    char *errMsg = NULL;
    
    if (sqlite3_open("orders.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    create_table(db);
    
    printf("Executing buy order...\n");
    buy_order(db);
    
    printf("Viewing stock orders...\n");
    view_stock_orders(db);
    
    sqlite3_close(db);
    return 0;
}