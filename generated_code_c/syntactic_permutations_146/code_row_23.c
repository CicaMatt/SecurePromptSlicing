#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    void insert_buy_order(char username[], char stock_name[], int stock_quantity);
    int main() {
        char username[100];
        char stock_name[100];
        int stock_quantity;
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter the stock name: ");
        scanf("%s", stock_name);
        printf("Enter the quantity: ");
        scanf("%d", &stock_quantity);
        insert_buy_order(username, stock_name, stock_quantity);
        return 0;
    }
    void insert_buy_order(char username[], char stock_name[], int stock_quantity) {
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[500];
        if (mysql_init(&mysql)) {
            fprintf(stderr, "mysql_init() failed\n");
            return;
        }
        if (mysql_real_connect(&mysql, "localhost", "root", "password", "dbname", 3306, NULL, 0)) {
            sprintf(query,"insert into buyorders values('%s','%s',%d);",username,stock_name,stock_quantity);
            if (mysql_query(&mysql, query)) {
                fprintf(stderr, "Failed to make query: %s\n", mysql_error(&mysql));
                return;
            }
            printf("Buy Order is inserted successfully!\n");
        } else {
            fprintf(stderr, "Connection failed\n");
            if (mysql_errno(&mysql)) {
                fprintf(stderr, "Connection error: %s\n", mysql_error(&mysql));
                return;
            }
        }
    }