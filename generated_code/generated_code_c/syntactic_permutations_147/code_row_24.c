#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    
    void buy_order(char *stock, int quantity) {
        char query[1024];
        sprintf(query, "INSERT INTO stocks (name, quantity) VALUES ('%s', '%d')", stock, quantity);
        mysql_query(query);
     }
     
    void stock_view() {
        printf("Stock name: %s\nStock quantity:%d\n", mysql_fetch_field(0), mysql_fetch_field(1));
    }
    
    int main() {
        char *stock = "ABC";
        int quantity = 10;
        buy_order(stock, quantity);
        stock_view();
        return 0;
    }