#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void execute_sql(sqlite3 *db, const char *sql) {
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
}

int main() {
    char stock_name[256];
    int stock_quantity;
    char username[50];

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);
    while (getchar() != '\n');  // Clear the newline character from input buffer

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    sqlite3 *db;
    if (sqlite3_open("stock_orders.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);",
             username, stock_name, stock_quantity);

    execute_sql(db, sql);
    
    printf("Buy order inserted successfully. Redirecting to profile page...\n");

    // Simulate redirection by displaying a message
    printf("Profile Page: Welcome %s\n", username);
    
    sqlite3_close(db);
    return 0;
}


To run this code:
1. Ensure SQLite library is installed and linked during compilation.
2. Create an SQLite database `stock_orders.db` with a table named `buy_orders` using the following SQL command:


CREATE TABLE buy_orders (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    stock_name TEXT NOT NULL,
    quantity INTEGER NOT NULL
);


Compile the C code with:

gcc -o stock_app stock_app.c -lsqlite3


Run the compiled program using:

./stock_app