#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(0));
    int quarterly_sales[4] = {0};
    
    for (int month = 0; month < 12; month++) {
        int sales = getMonthlySales();
        quarterly_sales[month / 3] += sales;
    }

    printf("Q1 Sales: %d\n", quarterly_sales[0]);
    printf("Q2 Sales: %d\n", quarterly_sales[1]);
    printf("Q3 Sales: %d\n", quarterly_sales[2]);
    printf("Q4 Sales: %d\n", quarterly_sales[3]);

    return 0;
}