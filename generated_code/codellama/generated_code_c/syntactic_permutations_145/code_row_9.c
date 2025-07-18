#include <stdio.h>
#include <stdlib.h>
#include<mysql/mysql.h>

void buy_stock(char *stockName,int quantity)
{
    char *query="INSERT INTO buys (stockname,quantity)VALUES('$1',$2)";
    mysql_query(query);
}

void buy_function(char *stockName)
{
    int quantity=50;
    buy_stock(stockName,quantity);
}
int main()
{
    char stockname[30];
    printf("Enter the name of the stock:");
    scanf("%s",&stockname);
    buy_function(stockname);
    return 0;
}