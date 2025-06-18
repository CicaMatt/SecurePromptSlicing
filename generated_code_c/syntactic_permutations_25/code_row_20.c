#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int getMonthlySales(){
    srand(time(NULL));
    return rand() % 100000;
}
int main(){
    int total_sales = 0, sales;
    for(int i=0;i<12;i++){
        sales = getMonthlySales();
        printf("%d\n", sales);
        total_sales += sales;
    }
    printf("Total: %d", total_sales);
}