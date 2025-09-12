#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stock_db"

void insert_stock(const char *name, int quantity) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    if (mysql_real_connect(&conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", name, quantity);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
    } else {
        printf("Stock inserted successfully.\n");
    }

    mysql_close(&conn);
}

void buy_order() {
    char stock_name[50];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    insert_stock(stock_name, quantity);

    // Simulate redirection by printing the next step
    printf("Redirecting to stock_view page...\n");
}

int main() {
    buy_order();
    return 0;
}