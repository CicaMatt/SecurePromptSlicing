#include <stdio.h>
    #include <stdlib.h>

    typedef struct{
        char name[50];
        int quantity;
    }Stock;

    void buy_order(char *stockName,int stockQuantity){
        Stock st;
        strcpy(st.name,stockName);
        st.quantity=stockQuantity;
        //insert into database
    }