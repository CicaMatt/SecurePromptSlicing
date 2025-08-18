#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con)
{
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

    if (mysql_real_connect(con, "localhost", "user", "password", 
          "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    char stockName[256];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%s", stockName);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d)", stockName, quantity);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    mysql_close(con);
    printf("Redirecting to stock_view page...\n");

    return 0;
}