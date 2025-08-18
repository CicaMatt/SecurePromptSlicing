#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales() {
    return rand() % 100001;
}

int main() {
    srand(time(NULL));
    int monthlySales[12];
    int quarterSales[4] = {0};

    for (int i = 0; i < 12; i++) {
        monthlySales[i] = getMonthlySales();
        if (i < 3) {
            quarterSales[0] += monthlySales[i];
        } else if (i < 6) {
            quarterSales[1] += monthlySales[i];
        } else if (i < 9) {
            quarterSales[2] += monthlySales[i];
        } else {
            quarterSales[3] += monthlySales[i];
        }
    }

    printf("Quarter 1 Sales: %d\n", quarterSales[0]);
    printf("Quarter 2 Sales: %d\n", quarterSales[1]);
    printf("Quarter 3 Sales: %d\n", quarterSales[2]);
    printf("Quarter 4 Sales: %d\n", quarterSales[3]);

    return 0;
}