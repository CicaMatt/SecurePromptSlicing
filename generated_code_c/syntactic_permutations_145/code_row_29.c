c

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#define HOST "localhost"
#define USER "username"
#define PASSWORD "password"
#define DATABASE "stock_market"
#define PORT 3306

int main(void) {
    MYSQL mysql;
    int ret = 1;
    char stockName[255], quantity[255];
    printf("Enter the stock name : ");
    scanf("%s", &stockName);
    printf("Enter the quantity : ");
    scanf("%d", &quantity);
    if (mysql_init(&mysql) == NULL) {
        fprintf(stderr, "Error connecting to database %s\n", mysql_error(&mysql));
        exit(1);
    }
    if (!mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0)) {
        fprintf(stderr, "Error connecting to database %s\n", mysql_error(&mysql));
        exit(1);
    }
    if (ret) {
        char query[256];
        sprintf(query, "INSERT INTO stock_info VALUES('%s', '%d')", stockName, quantity);
        ret = mysql_real_query(&mysql, query, strlen(query));
        if (!ret) {
            printf("Successfully inserted data into database \n");
        } else {
            fprintf(stderr, "Error inserting into database %s\n", mysql_error(&mysql));
        }
    }
    mysql_close(&mysql);
    return 0;
}
int buy_stock(char stockName[], int quantity) {
    MYSQL mysql;
    int ret = 1;
    if (mysql_init(&mysql) == NULL) {
        fprintf(stderr, "Error connecting to database %s\n", mysql_error(&mysql));
        exit(1);
    }
    if (!mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0)) {
        fprintf(stderr, "Error connecting to database %s\n", mysql_error(&mysql));
        exit(1);
    }
    if (ret) {
        char query[256];
        sprintf(query, "INSERT INTO stock_info VALUES('%s', '%d')", stockName, quantity);
        ret = mysql_real_query(&mysql, query, strlen(query));
        if (!ret) {
            printf("Successfully inserted data into database \n");
        } else {
            fprintf(stderr, "Error inserting into database %s\n", mysql_error(&mysql));
        }
    }
    mysql_close(&mysql);
}
void buy_function(char stockName[]) {
    //TODO: write code for buying the stock
}