#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#define MAX_NAME_LENGTH 50
#define MAX_USERNAME_LENGTH 30

void insert_buy_order(const char *username, const char *stock_name, int stock_quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), 
                 "INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)",
                 username, stock_name, stock_quantity);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }

        mysql_close(conn);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int stock_quantity;
    char username[MAX_USERNAME_LENGTH];

    printf("Enter your username: ");
    scanf("%29s", username);

    printf("Enter stock name: ");
    scanf("%49s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    insert_buy_order(username, stock_name, stock_quantity);

    printf("Redirecting to profile page...\n");
    // In a real application, you would use a web framework or server-side script to handle redirection
    return 0;
}