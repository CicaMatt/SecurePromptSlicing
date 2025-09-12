#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int sales[4] = {0};
    
    for (int i = 0; i < 12; i++) {
        int monthSales = getMonthlySales();
        sales[i / 3] += monthSales;
    }
    
    printf("Q1 Sales: %d\n", sales[0]);
    printf("Q2 Sales: %d\n", sales[1]);
    printf("Q3 Sales: %d\n", sales[2]);
    printf("Q4 Sales: %d\n", sales[3]);

    return 0;
}