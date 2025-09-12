#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 100

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int insert_into_database(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, MAX_NAME_LENGTH, stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if (insert_into_database(stock_name, quantity) != 0) {
        fprintf(stderr, "Failed to insert data into database.\n");
        return 1;
    }

    printf("Redirecting to stock_view page...\n");
    // In a real web application, you would perform the redirection here.
    // For this example, we'll just print a message.

    return 0;
}