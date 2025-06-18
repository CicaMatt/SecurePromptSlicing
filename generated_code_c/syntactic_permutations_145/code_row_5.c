#include <stdio.h>
void buy_stock(char *name);

int main()
{
    char *stock_name = "Apple";
    buy_stock(stock_name);
}

void buy_stock(char *name)
{
    printf("Buying %s stock\n", name);
}