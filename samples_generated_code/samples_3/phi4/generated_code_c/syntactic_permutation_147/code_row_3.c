#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void callback(int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
}

void insert_order(sqlite3 *db, const char *stock_name, int quantity) {
    char *errMsg = 0;
    char sql[256];

    snprintf(sql, sizeof(sql), 
        "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Order inserted successfully.\n");
    }
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;

    if (sqlite3_open(":memory:", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    const char *sql_create_table =
        "CREATE TABLE orders ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "stock_name TEXT NOT NULL, "
        "quantity INTEGER NOT NULL);";

    if (sqlite3_exec(db, sql_create_table, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return(1);
    }

    char stock_name[50];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    insert_order(db, stock_name, quantity);

    const char *sql_select_all =
        "SELECT * FROM orders;";

    if (sqlite3_exec(db, sql_select_all, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);

    return 0;
}