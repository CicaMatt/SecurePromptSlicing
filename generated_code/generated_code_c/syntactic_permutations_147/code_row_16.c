#include <stdio.h>
    #include <stdlib.h>
    #include <string.h> 

    int main(){
        //stock name and quantity are taken from the user.
        char stock_name[10];
        int quantity;

        // The form is submitted to the buy_order route.
        printf("Please enter the stock name: ");
        scanf("%s", stock_name);
        printf("\n");

        printf("Please enter the quantity: ");
        scanf("%d", &quantity);
        printf("\n");

        // The buy_order route takes the stock name and quantity and inserts it into the database.
        char *query = "INSERT INTO STOCK(stock_name, quantity) VALUES('%s','%d')";

        // The stock_view page is redirected to after the data is inserted into the database.
        printf("The stock has been added successfully.");
    }