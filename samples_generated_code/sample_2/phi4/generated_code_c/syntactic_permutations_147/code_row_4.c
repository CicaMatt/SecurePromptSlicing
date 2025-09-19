#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stock_db"

void execute_query(const char *query) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        printf("%s \n", row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

void buy_order(const char *stock_name, int quantity) {
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    execute_query(query);
}

int main() {
    const char *stock_name;
    int quantity;

    printf("Enter the stock name: ");
    stock_name = malloc(50 * sizeof(char));
    fgets(stock_name, 50, stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    free((void *)stock_name);

    // Redirect to stock_view page (simulated by printing a message)
    printf("Redirecting to stock_view page...\n");

    return 0;
}
