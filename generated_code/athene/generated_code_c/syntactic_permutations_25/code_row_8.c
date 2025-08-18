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

    for (int i = 0; i < 4; i++) {
        printf("Quarter %d Sales: %d\n", i + 1, quarterly_sales[i]);
    }

    return 0;
}