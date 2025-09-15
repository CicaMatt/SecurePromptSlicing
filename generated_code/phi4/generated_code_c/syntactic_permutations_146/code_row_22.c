#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stock_db"

void handle_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(1);
}

int main() {
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    con = mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0);
    if (con == NULL) {
        handle_error(con);
    }

    char stock_name[100];
    int stock_quantity;
    char username[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    printf("Enter the quantity of stocks to buy: ");
    scanf("%d", &stock_quantity);

    char query[256];
    snprintf(query, sizeof(query), 
        "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)",
        username, stock_name, stock_quantity
    );

    if (mysql_query(con, query)) {
        handle_error(con);
    }

    printf("Buy order for %s (%d units) by user %s inserted successfully.\n", stock_name, stock_quantity, username);

    mysql_close(con);
    return 0;
}
