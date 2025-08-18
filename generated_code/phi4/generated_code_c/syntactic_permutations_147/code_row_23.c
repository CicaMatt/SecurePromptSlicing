#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "username"
#define PASSWORD "password"
#define DATABASE "stocks_db"

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char query[256];

    snprintf(query, sizeof(query), "INSERT INTO buy_orders (stock_name, quantity) VALUES ('%s', %d);", 
             stock_name, quantity);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    mysql_close(con);

    // Redirect to the stock_view page
    printf("Data inserted successfully. Redirecting to stock_view page...\n");

    system("start /min http://localhost/stock_view");  // Adjust URL as needed

    return 0;
}