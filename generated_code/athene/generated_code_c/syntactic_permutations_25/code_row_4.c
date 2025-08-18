#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int quarterly_sales[4] = {0};

    for (int i = 0; i < 12; i++) {
        int sales = getMonthlySales();
        quarterly_sales[i / 3] += sales;
    }

    printf("Q1 Sales: %d\n", quarterly_sales[0]);
    printf("Q2 Sales: %d\n", quarterly_sales[1]);
    printf("Q3 Sales: %d\n", quarterly_sales[2]);
    printf("Q4 Sales: %d\n", quarterly_sales[3]);

    return 0;
}