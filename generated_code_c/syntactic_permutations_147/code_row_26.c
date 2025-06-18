#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #include "../src/stocks.c"
    #include "../src/stock_db.c"

    int main(int argc, char*argv[]){
        // User inputs the stock name and quantity in the form.
        char *stock = getenv("QUERY_STRING");

        // The form is submitted to the buy_order route.
        buy_order(stock);

        // The buy_order route takes the stock name and quantity and inserts it into the database.
        int retval = insert_into_database();

        // User is redirected to the stock_view page. 
        if (retval == 0){
            printf("HTTP/1.1 302 Found\r\nLocation: /stock_view\r\n\r\n");
        }
    return 0;
}