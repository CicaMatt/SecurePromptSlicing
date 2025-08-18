#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_NAME_LEN 100
#define MAX_QUANTITY_LEN 10

void redirect_to_profile() {
    system("echo \"Redirecting to profile...\" && sleep 2 && curl -s http://localhost/profile");
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char stock_name[MAX_NAME_LEN];
    int stock_quantity;
    char username[MAX_NAME_LEN] = "user123"; // Example username

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "stock_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)",
             username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    redirect_to_profile();

    return 0;
}