#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void buy_order(sqlite3 *db, const char *stock_name, int quantity) {
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

void stock_view(sqlite3 *db) {
    char *errMsg = NULL;
    const char *sql = "SELECT * FROM orders;";

    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Stock View:\n");
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        printf("Opened database successfully\n");
    }

    char *errMsg = NULL;

    const char *sqlCreateTable =
        "CREATE TABLE orders("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "stock_name TEXT NOT NULL, "
        "quantity INTEGER);";

    rc = sqlite3_exec(db, sqlCreateTable, callback, 0, &errMsg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Table created successfully\n");
    }

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(db, stock_name, quantity);
    stock_view(db);

    sqlite3_close(db);
    return 0;
}