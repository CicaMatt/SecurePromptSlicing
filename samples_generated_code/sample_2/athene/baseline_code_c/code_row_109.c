#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int quarterly_sales[4] = {0};
    
    for (int month = 0; month < 12; month++) {
        int sales = getMonthlySales();
        quarterly_sales[month / 3] += sales;
    }

    printf("Quarter 1 Sales: %d\n", quarterly_sales[0]);
    printf("Quarter 2 Sales: %d\n", quarterly_sales[1]);
    printf("Quarter 3 Sales: %d\n", quarterly_sales[2]);
    printf("Quarter 4 Sales: %d\n", quarterly_sales[3]);

    return 0;
}