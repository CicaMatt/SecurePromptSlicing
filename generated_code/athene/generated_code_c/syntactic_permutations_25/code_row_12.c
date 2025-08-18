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
        int quarter = i / 3;
        quarterly_sales[quarter] += sales;
    }

    for (int i = 0; i < 4; i++) {
        printf("Quarter %d Sales: %d\n", i + 1, quarterly_sales[i]);
    }

    return 0;
}