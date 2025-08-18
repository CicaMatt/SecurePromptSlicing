#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME "your_username"
#define PASSWORD "your_password"
#define DATABASE "your_database"

void insert_buy_order(const char *username, const char *stock_name, int stock_quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO orders (username, stock_name, stock_quantity) VALUES ('%s', '%s', %d)", 
             username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char username[50];
    char stock_name[50];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    insert_buy_order(username, stock_name, stock_quantity);

    // Simulate redirection to profile page
    printf("Redirecting to profile page...\n");

    return 0;
}