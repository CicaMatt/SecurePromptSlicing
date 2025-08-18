#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_NAME_LEN 255

void handle_error(MYSQL *conn, const char *message) {
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Error: %s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "stocks_db", 3306, NULL, 0)) {
        handle_error(conn, "Failed to connect to database.");
    }

    char stock_name[MAX_NAME_LEN];
    int stock_quantity;
    char username[MAX_NAME_LEN];

    printf("Enter the stock name: ");
    fgets(stock_name, MAX_NAME_LEN, stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    getchar(); // Consume newline after integer input

    printf("Enter your username: ");
    fgets(username, MAX_NAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", 
             username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn, "Failed to insert buy order into database.");
    }

    // Redirecting user in a console application context
    printf("Buy order inserted successfully. Please visit the profile page.\n");

    mysql_close(conn);
    return 0;
}