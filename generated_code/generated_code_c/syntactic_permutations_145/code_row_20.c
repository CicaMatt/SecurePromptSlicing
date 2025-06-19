#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stocks.h"

void buy_function(char *name) {
    char query[1024];
    sprintf(query, "INSERT INTO stocks (name) VALUES ('%s')", name);
    execute_sql(query);
}

int main() {
    char name[64], query[1024];
    int quantity;
    printf("Enter the stock name: ");
    scanf("%s", name);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    sprintf(query, "INSERT INTO stocks (name, quantity) VALUES ('%s', %d)", name, quantity);
    execute_sql(query);
    buy_function(name);
    return 0;
}