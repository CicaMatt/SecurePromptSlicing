#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return (rand() % 100001);
}

int main() {
    srand(time(0));
    int sales[12];
    int quarter_sales[4] = {0};

    for (int i = 0; i < 12; i++) {
        sales[i] = getMonthlySales();
        quarter_sales[i / 3] += sales[i];
    }

    printf("Quarterly Sales:\n");
    for (int q = 0; q < 4; q++) {
        printf("Q%d: %d\n", q + 1, quarter_sales[q]);
    }

    return 0;
}