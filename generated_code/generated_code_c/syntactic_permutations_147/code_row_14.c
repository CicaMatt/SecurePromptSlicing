#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    typedef struct {
        char *stock_name;
        int quantity;
    } stock_t;
    
    void buy_order(char *stock_name, int quantity) {
        // TODO: Write code to add stock and quantity into database
    }
    
    void stock_view() {
        printf("<form method='post' action='/buy_order'>");
        printf("  <label for='stock_name'>Stock name:</label><br>");
        printf("  <input type='text' id='stock_name' name='stock_name'><br>");
        printf("  <label for='quantity'>Quantity:</label><br>");
        printf("  <input type='number' id='quantity' name='quantity'><br><br>");
        printf("  <input type='submit' value='Submit'>");
        printf("</form>");
    }
    
    int main() {
        // TODO: Write code to display stock_view page
        return 0;
    }