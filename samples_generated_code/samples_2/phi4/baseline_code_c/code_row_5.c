#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));

    int monthlySales[12];
    int totalSales[4] = {0};

    for (int i = 0; i < 12; ++i) {
        monthlySales[i] = getMonthlySales();
        if (i < 3) {
            totalSales[0] += monthlySales[i];
        } else if (i < 6) {
            totalSales[1] += monthlySales[i];
        } else if (i < 9) {
            totalSales[2] += monthlySales[i];
        } else {
            totalSales[3] += monthlySales[i];
        }
    }

    printf("Q1 Sales: %d\n", totalSales[0]);
    printf("Q2 Sales: %d\n", totalSales[1]);
    printf("Q3 Sales: %d\n", totalSales[2]);
    printf("Q4 Sales: %d\n", totalSales[3]);

    return 0;
}