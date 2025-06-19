#include <stdio.h>
    
    struct order {
        char name[50];
        int quantity;
    };
    
    void buy_stock(struct order);
    void buy_function(char*);
    
    int main() {
      struct order o = {.name="ABC", .quantity=10};
      buy_stock(o);
    }
    
    void buy_stock(struct order o) {
        printf("Buying %s stock\n", o.name);
        buy_function(o.name);
    }
    
    void buy_function(char* name) {
        printf("%s function called\n", name);
    }